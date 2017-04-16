#include <errno.h>
#include <string.h>
#include <sys/reboot.h>
#include <syslog.h>
#include <unistd.h>
#include "fs.h"
#include "net.h"
#include "proc.h"

void hang();
void launch_recovery();

int main(int argc, const char **argv) {
    openlog("init", LOG_CONS | LOG_NDELAY, LOG_DAEMON);
    if (mount_devfs() < 0) {
        syslog(LOG_EMERG, "Failed to mount /dev: %s", strerror(errno));
    } else if (mount_all() < 0) {
        syslog(LOG_CRIT, "Failed to mount all filesystems: %s", strerror(errno));
        launch_recovery(0);
    } else {
        syslog(LOG_INFO, "Launching initial container...");
        if (launch_process1("/data/com.github.centaurios.application-control/bin/appctl", "init") < 0) {
            syslog(LOG_EMERG, "Failed to launch container: %s", strerror(errno));
            launch_recovery(1);
        } else {
            syslog(LOG_INFO, "Initial container is running.");
            if (cleanup_recovery() < 0) {
                syslog(LOG_WARNING, "Unable to clean up recovery files: %s", strerror(errno));
            }
            if (start_socket() < 0) {
                syslog(LOG_EMERG, "Socket controller failed: %s", strerror(errno));
            } else {
                syslog(LOG_INFO, "Shutting down system.");
                sync();
                if (reboot(RB_POWER_OFF) < 0) {
                    syslog(LOG_CRIT, "Unable to shut down system: %s", strerror(errno));
                }
            }
        }
    }
    hang();
    return 0;
}

void hang() {
    closelog();
    while (1) {
        sleep((unsigned) -1);
    }
}

void launch_recovery(int is_jailed) {
    if (mount_recovery(is_jailed) < 0) {
        syslog(LOG_EMERG, "Failed to mount recovery filesystem: %s", strerror(errno));
    } else {
        syslog(LOG_INFO, "Launching recovery tools...");
        if (launch_process("/sbin/recover") < 0) {
            syslog(LOG_EMERG, "Failed to launch recovery tools: %s", strerror(errno));
        }
    }
    hang();
}

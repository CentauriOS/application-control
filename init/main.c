#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/reboot.h>
#include <syslog.h>
#include <unistd.h>
#include <common/paths.h>
#include <init/fs.h>
#include <init/proc.h>

void hang();
void launch_recovery();

int main(int argc, const char **argv) {
    openlog("init", LOG_CONS | LOG_NDELAY, LOG_DAEMON);
    if (mount_devfs() < 0) {
        syslog(LOG_EMERG, "Failed to mount " DEVICES_DIR ": %s", strerror(errno));
    } else if (mount_all() < 0) {
        syslog(LOG_CRIT, "Failed to mount all filesystems: %s", strerror(errno));
        launch_recovery(0);
    } else {
        syslog(LOG_INFO, "Launching initial container...");
        if (launch_process1(START_APPLICATION, DATA_DIR "/" START_CONTAINER, START_APPLICATION_PARAM) < 0) {
            syslog(LOG_EMERG, "Failed to launch container: %s", strerror(errno));
            launch_recovery(1);
        } else {
            syslog(LOG_INFO, "Initial container is running.");
            if (cleanup_recovery() < 0) {
                syslog(LOG_WARNING, "Unable to clean up recovery files: %s", strerror(errno));
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
        if (launch_process(RECOVERY_APPLICATION) < 0) {
            syslog(LOG_EMERG, "Failed to launch recovery tools: %s", strerror(errno));
        }
    }
    hang();
}

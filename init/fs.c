#include <errno.h>
#include <syslog.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
#include "fs.h"

int mount_devfs() {
    if (mount("none", "/dev", "devtmpfs", 0, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /dev");
        return -1;
    } else {
        return 0;
    }
}

int mount_all() {
    errno = ENOSYS;
    return -1;
}

int mount_recovery() {
    if (access("/root", F_OK) < 0 && mkdir("/root", 0777) < 0) {
        syslog(LOG_EMERG, "Unable to create /root");
        return -1;
    } else if (mount("/recovery.iso", "/root", "ext4", MS_RDONLY, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /recovery.iso");
        return -1;
    } else if (mount("/dev", "/root/dev", NULL, MS_MOVE, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to move /dev");
        return -1;
    } else if (chdir("/root") < 0) {
        syslog(LOG_EMERG, "Unable to chdir into /root");
        return -1;
    } else if (mount(".", "/", NULL, MS_MOVE, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to switch roots");
        return -1;
    } else if (chroot(".") < 0) {
        syslog(LOG_EMERG, "Unable to chroot");
        return -1;
    } else if (chdir("/") < 0) {
        syslog(LOG_EMERG, "Unable to chdir into /");
        return -1;
    } else if (mount("none", "/tmp", "tmpfs", 0, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /tmp");
        return -1;
    } else if (mount("none", "/proc", "proc", 0, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /proc");
        return -1;
    } else if (mount("none", "/sys", "sysfs", 0, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /sys");
        return -1;
    } else {
        return 0;
    }
}

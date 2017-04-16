#include <errno.h>
#include <fcntl.h>
#include <mntent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
#include <init/fs.h>

int real_root = -1;

int mount_entry(struct mntent *ent);

int mount_devfs() {
    if (mount("none", "/dev", "devtmpfs", 0, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /dev");
        return -1;
    } else {
        return 0;
    }
}

int mount_all() {
    FILE *fstab = setmntent("/fstab", "r");
    if (fstab) {
        if (access("/root", F_OK) < 0 && mkdir("/root", 0777) < 0) {
            syslog(LOG_EMERG, "Unable to create /root");
            return -1;
        } else {
            struct mntent *ent;
            while (ent = getmntent(fstab)) {
                if (strcmp(ent->mnt_dir, "/") == 0) {
                    struct mntent ent2;
                    ent2.mnt_fsname = ent->mnt_fsname;
                    ent2.mnt_dir = "/root";
                    ent2.mnt_type = ent->mnt_type;
                    ent2.mnt_opts = ent->mnt_opts;
                    if (mount_entry(&ent2) < 0) {
                        int e = errno;
                        syslog(LOG_EMERG, "Unable to mount rootfs");
                        endmntent(fstab);
                        errno = e;
                        return -1;
                    } else {
                        fseek(fstab, 0, SEEK_SET);
                        if (mount("/dev", "/root/dev", NULL, MS_MOVE, NULL) < 0) {
                            syslog(LOG_EMERG, "Unable to move /dev");
                            return -1;
                        } else if (chdir("/root") < 0) {
                            syslog(LOG_EMERG, "Unable to chdir into /root");
                            int e = errno;
                            if (mount("/root/dev", "/dev", NULL, MS_MOVE, NULL) < 0) {
                                syslog(LOG_CRIT, "Unable to move /dev back");
                                mount_devfs();
                            }
                            errno = e;
                            return -1;
                        } else if (mount(".", "/", NULL, MS_MOVE, NULL) < 0) {
                            syslog(LOG_EMERG, "Unable to switch roots");
                            int e = errno;
                            if (mount("/root/dev", "/dev", NULL, MS_MOVE, NULL) < 0) {
                                syslog(LOG_CRIT, "Unable to move /dev back");
                                mount_devfs();
                            }
                            errno = e;
                            return -1;
                        } else {
                            real_root = open("/", O_RDONLY);
                            if (real_root < 0) {
                                syslog(LOG_CRIT, "Unable to open /");
                            }
                            if (chroot(".") < 0) {
                                syslog(LOG_EMERG, "Unable to chroot");
                                int e = errno;
                                if (mount("/root/dev", "/dev", NULL, MS_MOVE, NULL) < 0) {
                                    syslog(LOG_CRIT, "Unable to move /dev back");
                                    mount_devfs();
                                }
                                errno = e;
                                return -1;
                            } else if (chdir("/") < 0) {
                                syslog(LOG_EMERG, "Unable to chdir into /");
                                int e = errno;
                                if (mount("/root/dev", "/dev", NULL, MS_MOVE, NULL) < 0) {
                                    syslog(LOG_CRIT, "Unable to move /dev back");
                                    mount_devfs();
                                }
                                errno = e;
                                return -1;
                            } else {
                                while (ent = getmntent(fstab)) {
                                    if (strcmp(ent->mnt_dir, "/") != 0) {
                                        if (mount_entry(ent) < 0) {
                                            int e = errno;
                                            syslog(LOG_EMERG, "Unable to mount filesystem %s", ent->mnt_fsname);
                                            endmntent(fstab);
                                            if (mount("/root/dev", "/dev", NULL, MS_MOVE, NULL) < 0) {
                                                syslog(LOG_CRIT, "Unable to move /dev back");
                                                mount_devfs();
                                            }
                                            errno = e;
                                            return -1;
                                        }
                                    }
                                }
                                endmntent(fstab);
                                return 0;
                            }
                        }
                    }
                }
            }
            endmntent(fstab);
            syslog(LOG_EMERG, "Root filesystem not found in fstab");
            errno = ENOKEY;
            return -1;
        }
    } else {
        syslog(LOG_EMERG, "Unable to open fstab");
        return -1;
    }
    return 0;
}

int mount_recovery(int is_jailed) {
    if (is_jailed) {
        if (fchdir(real_root) < 0) {
            syslog(LOG_EMERG, "Unable to chdir back to the real /");
            return -1;
        } else if (chroot(".") < 0) {
            syslog(LOG_EMERG, "Unable to chroot back to the real /");
            return -1;
        } else if (mount_devfs() < 0) {
            syslog(LOG_EMERG, "Unable to remount /dev");
            return -1;
        }
    }
    if (access("/recovery", F_OK) < 0 && mkdir("/recovery", 0777) < 0) {
        syslog(LOG_EMERG, "Unable to create /recovery");
        return -1;
    } else if (mount("/recovery.iso", "/recovery", "ext4", MS_RDONLY, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to mount /recovery.iso");
        return -1;
    } else if (mount("/dev", "/recovery/dev", NULL, MS_MOVE, NULL) < 0) {
        syslog(LOG_EMERG, "Unable to move /dev");
        return -1;
    } else if (chdir("/recovery") < 0) {
        syslog(LOG_EMERG, "Unable to chdir into /recovery");
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

int cleanup_recovery() {
    int cwdfd = open(".", O_RDONLY);
    if (fchdir(real_root) < 0) {
        syslog(LOG_WARNING, "Unable to chdir back to the real /");
        return -1;
    } else {
        int r = 0;
        int e = 0;
        if (unlink("recovery.iso") < 0) {
            syslog(LOG_WARNING, "Unable to remove /recovery.iso");
            e = r == 0 ? errno : e;
            r = -1;
        } else if (unlink("init") < 0) {
            syslog(LOG_WARNING, "Unable to remove /init");
            e = r == 0 ? errno : e;
            r = -1;
        } else if (unlink("fstab") < 0) {
            syslog(LOG_WARNING, "Unable to remove /fstab");
            e = r == 0 ? errno : e;
            r = -1;
        } else if (close(real_root) < 0) {
            syslog(LOG_WARNING, "Unable to close /");
            e = r == 0 ? errno : e;
            r = -1;
        } else if (fchdir(cwdfd) < 0) {
            syslog(LOG_EMERG, "Unable to chdir back to the fake /");
            return -1;
        } else if (close(cwdfd) < 0) {
            syslog(LOG_WARNING, "Unable to close fake /");
            e = r == 0 ? errno : e;
            r = -1;
        }
        errno = e;
        return r;
    }
}

int mount_entry(struct mntent *ent) {
    int mountflags = 0;
    int max_data_len = strlen(ent->mnt_opts);
    char *data = (char *) malloc(max_data_len);
    char *inpos = ent->mnt_opts;
    char *inend = inpos + max_data_len;
    char *instart = inpos;
    char *outpos = data;
    int fail = 1;
    while (inpos < inend) {
        if (*inpos == ',') {
            if (strncmp("async", instart, inpos - instart) == 0) {
                mountflags &= ~MS_SYNCHRONOUS;
            } else if (strncmp("atime", instart, inpos - instart) == 0) {
                mountflags &= ~MS_NOATIME;
            } else if (strncmp("noatime", instart, inpos - instart) == 0) {
                mountflags |= MS_NOATIME;
            } else if (strncmp("defaults", instart, inpos - instart) == 0) {
                mountflags &= ~(MS_RDONLY | MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_SYNCHRONOUS);
            } else if (strncmp("dev", instart, inpos - instart) == 0) {
                mountflags &= ~MS_NODEV;
            } else if (strncmp("nodev", instart, inpos - instart) == 0) {
                mountflags |= MS_NODEV;
            } else if (strncmp("diratime", instart, inpos - instart) == 0) {
                mountflags &= ~MS_NODIRATIME;
            } else if (strncmp("nodiratime", instart, inpos - instart) == 0) {
                mountflags |= MS_NODIRATIME;
            } else if (strncmp("dirsync", instart, inpos - instart) == 0) {
                mountflags |= MS_DIRSYNC;
            } else if (strncmp("exec", instart, inpos - instart) == 0) {
                mountflags &= ~MS_NOEXEC;
            } else if (strncmp("noexec", instart, inpos - instart) == 0) {
                mountflags |= MS_NOEXEC;
            } else if (strncmp("mand", instart, inpos - instart) == 0) {
                mountflags |= MS_MANDLOCK;
            } else if (strncmp("nomand", instart, inpos - instart) == 0) {
                mountflags &= ~MS_MANDLOCK;
            } else if (strncmp("nofail", instart, inpos - instart) == 0) {
                fail = 0;
            } else if (strncmp("relatime", instart, inpos - instart) == 0) {
                mountflags |= MS_RELATIME;
            } else if (strncmp("norelatime", instart, inpos - instart) == 0) {
                mountflags &= ~MS_RELATIME;
            } else if (strncmp("strictatime", instart, inpos - instart) == 0) {
                mountflags |= MS_STRICTATIME;
            } else if (strncmp("nostrictatime", instart, inpos - instart) == 0) {
                mountflags &= ~MS_STRICTATIME;
            } else if (strncmp("lazytime", instart, inpos - instart) == 0) {
                mountflags |= MS_LAZYTIME;
            } else if (strncmp("nolazytime", instart, inpos - instart) == 0) {
                mountflags &= ~MS_LAZYTIME;
            } else if (strncmp("suid", instart, inpos - instart) == 0) {
                mountflags &= ~MS_NOSUID;
            } else if (strncmp("nosuid", instart, inpos - instart) == 0) {
                mountflags |= MS_NOSUID;
            } else if (strncmp("silent", instart, inpos - instart) == 0) {
                mountflags |= MS_SILENT;
            } else if (strncmp("loud", instart, inpos - instart) == 0) {
                mountflags &= ~MS_SILENT;
            } else if (strncmp("remount", instart, inpos - instart) == 0) {
                mountflags |= MS_REMOUNT;
            } else if (strncmp("ro", instart, inpos - instart) == 0) {
                mountflags |= MS_RDONLY;
            } else if (strncmp("rw", instart, inpos - instart) == 0) {
                mountflags &= ~MS_RDONLY;
            } else if (strncmp("sync", instart, inpos - instart) == 0) {
                mountflags |= MS_SYNCHRONOUS;
            } else if (strncmp("bind", instart, inpos - instart) == 0) {
                mountflags |= MS_BIND;
            } else if (strncmp("move", instart, inpos - instart) == 0) {
                mountflags |= MS_MOVE;
            } else {
                if (data != outpos) {
                    *data++ = ',';
                }
                while (instart < inpos) {
                    *data++ = *instart++;
                }
            }
        } else {
            ++inpos;
        }
    }
    *outpos = 0;
    int r = mount(ent->mnt_fsname, ent->mnt_dir, ent->mnt_type, mountflags, data);
    int e = errno;
    free(data);
    errno = e;
    return fail * r;
}

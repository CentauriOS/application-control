#ifndef CENTAURI_PROC_H
#define CENTAURI_PROC_H

int launch_process(const char *path);

int launch_process1(const char *path, const char *chroot, const char *arg1);

#endif

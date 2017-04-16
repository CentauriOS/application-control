#ifndef CENTAURI_FS_H
#define CENTAURI_FS_H

int mount_devfs();

int mount_all();

int mount_recovery(int is_jailed);

int cleanup_recovery();

#endif

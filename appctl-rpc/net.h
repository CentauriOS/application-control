#ifndef CENTAURI_NET_H
#define CENTAURI_NET_H

int net_launch(int stdin, int stdout, int stderr, int cwd, int uid, int gid, int argc, const char **argv, const char *path, const char *container);

#endif

#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <common/paths.h>
#include <appctl-rpc/string.h>
#include <appctl-rpc/net.h>

int net_launch(int stdin, int stdout, int stderr, int cwd, int uid, int gid, int argc, const char **argv, const char *path, const char *container) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        writestr(stdout, "Unable to create socket\n");
        return errno;
    }
    struct sockaddr_un addr = {
        .sun_family = AF_UNIX,
        .sun_path = APPCTL_SOCKET
    };
    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        writestr(stdout, "Unable to connect to socket\n");
        return errno;
    }
    struct msghdr msg = { 0 };
    char buffer[CMSG_SPACE(sizeof(int) * 4)] = { 0 };
    struct iovec io = {
        .iov_base = "",
        .iov_len = 1
    };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buffer;
    msg.msg_controllen = sizeof(buffer);
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(int) * 4);
    int *fds = (int *) CMSG_DATA(cmsg);
    fds[0] = stdin;
    fds[1] = stdout;
    fds[2] = stderr;
    fds[3] = cwd;
    msg.msg_controllen = cmsg->cmsg_len;
    if (sendmsg(fd, &msg, 0) < 0) {
        writestr(stdout, "Error sending information\n");
        return errno;
    }
    int pathlen = strlen(path);
    int containerlen = strlen(container);
    char data[12] = {
        (argc >> 24) & 0xFF, (argc >> 16) & 0xFF, (argc >> 8) & 0xFF, argc & 0xFF,
        (pathlen >> 24) & 0xFF, (pathlen >> 16) & 0xFF, (pathlen >> 8) & 0xFF, pathlen & 0xFF,
        (containerlen >> 24) & 0xFF, (containerlen >> 16) & 0xFF, (containerlen >> 8) & 0xFF, containerlen & 0xFF
    };
    if (write(fd, data, 12) < 0) {
        writestr(stdout, "Error sending information\n");
        return errno;
    }
    if (write(fd, path, pathlen) < 0) {
        writestr(stdout, "Error sending information\n");
        return errno;
    }
    if (write(fd, container, containerlen) < 0) {
        writestr(stdout, "Error sending information\n");
        return errno;
    }
    int i;
    for (i = 0; i < argc; ++i) {
        int len = strlen(argv[i]);
        data[0] = (len >> 24) & 0xFF;
        data[1] = (len >> 16) & 0xFF;
        data[2] = (len >> 8) & 0xFF;
        data[3] = len & 0xFF;
        if (write(fd, data, 4) < 0) {
            writestr(stdout, "Error sending information\n");
            return errno;
        }
        if (write(fd, argv[i], len) < 0) {
            writestr(stdout, "Error sending information\n");
            return errno;
        }
    }
    if (read(fd, data, 4) < 0) {
        writestr(stdout, "Error reading information\n");
        return errno;
    }
    close(fd);
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

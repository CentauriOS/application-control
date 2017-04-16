#include <errno.h>
#include <string.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include "net.h"

int start_socket() {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        syslog(LOG_EMERG, "Unable to create contol socket: %s", strerror(errno));
        return fd;
    }
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    memcpy(addr.sun_path, "/tmp/.centauri", strlen("/tmp/.centauri"));
    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        syslog(LOG_EMERG, "Unable to bind control socket: %s", strerror(errno));
        return -1;
    }
    if (listen(fd, 1) < 0) {
        syslog(LOG_EMERG, "Unable to listen on the control socket: %s", strerror(errno));
        return -1;
    }
    int cfd = accept(fd, 0, 0);
    if (cfd < 0) {
        syslog(LOG_CRIT, "Unable to accept client socket: %s", strerror(errno));
        return cfd;
    }
    // ... //
    write(cfd, "Hello, world!\n", strlen("Hello, world!\n"));
    // ... //
    close(cfd);
    close(fd);
    return 0;
}

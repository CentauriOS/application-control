#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void open_shell(const char *tty);

int main(int argc, const char **argv) {
    if (setenv("PS1", "\\033[34m\\u@recovery:\\w\\$\\033[0m ", 1) < 0) {
        fprintf(stderr, "Error setting PS1: %s\n", strerror(errno));
    }
    open_shell("/dev/tty1");
    open_shell("/dev/ttyS0");
}

void open_shell(const char *tty) {
    pid_t pid = fork();
    if (pid == 0) {
        if (setsid() < 0) {
            fprintf(stderr, "Error setting SID: %s\n", strerror(errno));
        }
        int fd = open(tty, O_RDWR);
        if (fd < 0) {
            fprintf(stderr, "Unable to open tty: %s\n", strerror(errno));
        } else {
            dup2(fd, STDIN_FILENO);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
        }
        if (execl("/bin/bash", "/bin/bash", "--noprofile", "--norc", "-l", NULL) < 0) {
            fprintf(stderr, "Unable to open shell: %s\n", strerror(errno));
        }
    } else if (pid < 0) {
        fprintf(stderr, "Unable to spawn process: %s\n", strerror(errno));
    }
}

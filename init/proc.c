#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <unistd.h>
#include <init/proc.h>

int launch_process_generic(void *data, const char *chroot, int (*exec)(void *));
int launch_process_exec(void *data);
int launch_process_exec1(void *data);

int launch_process(const char *path) {
    return launch_process_generic((char *) path, NULL, launch_process_exec);
}

int launch_process1(const char *path, const char *chroot, const char *arg1) {
    void *data[2];
    data[0] = (char *) path;
    data[1] = (char *) arg1;
    return launch_process_generic(data, chroot, launch_process_exec1);
}

int launch_process_generic(void *data, const char *root, int (*exec)(void *)) {
    pid_t pid = fork();
    if (pid == 0) {
        if (root != NULL) {
            chroot(root);
        }
        if (exec(data) < 0) {
            exit(errno);
        }
    } else if (pid < 0) {
        return pid;
    } else {
        sleep(1);
        int status = 0;
        if (waitpid(pid, &status, WNOHANG) < 0) {
            syslog(LOG_EMERG, "Unable to get process status");
            return -1;
        } else {
            errno = WEXITSTATUS(status);
            return -errno;
        }
    }
}

int launch_process_exec(void *data) {
    return execl((char *) data, (char *) data, NULL);
}

int launch_process_exec1(void *data) {
    return execl(((char **) data)[0], ((char **) data)[0], ((char **) data)[1], NULL);
}

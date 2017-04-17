#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <appctl-rpc/string.h>
#include <appctl-rpc/wrapper.h>
#include <appctl-rpc/net.h>

int main(int argc, const char **argv) {
    const char *path = NULL;
    const char *container = NULL;
    if (is_process_wrapper()) {
        path = get_process_wrapper_path();
        container = get_process_wrapper_container();
    } else if (argc == 4 && streq(argv[1], "wrap")) {
        if (wrap(argv[0], argv[2], argv[3]) < 0) {
            writestr(STDOUT_FILENO, "Unable to create process wrapper\n");
            return errno;
        } else {
            writestr(STDOUT_FILENO, "Successfully created process wrapper\n");
            return EXIT_SUCCESS;
        }
    }
    int cwd = open(".", O_RDONLY);
    if (cwd < 0) {
        writestr(STDOUT_FILENO, "Unable to open current directory\n");
        return EXIT_FAILURE;
    }
    int uid = getuid();
    int gid = getgid();
    return net_launch(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, cwd, uid, gid, argc, argv, path, container);
}

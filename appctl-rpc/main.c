#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <appctl-rpc/string.h>
#include <appctl-rpc/wrapper.h>

int main(int argc, const char **argv) {
    if (argc == 4 && streq(argv[1], "wrap")) {
        if (wrap(argv[0], argv[2], argv[3]) < 0) {
            writestr(STDOUT_FILENO, "Unable to create process wrapper\n");
            return errno;
        } else {
            writestr(STDOUT_FILENO, "Successfully created process wrapper\n");
            return EXIT_SUCCESS;
        }
    } else if (is_process_wrapper()) {
        writestr(STDOUT_FILENO, "Launching process ");
        writestr(STDOUT_FILENO, get_process_wrapper_path());
        writestr(STDOUT_FILENO, " in container ");
        writestr(STDOUT_FILENO, get_process_wrapper_container());
        writestr(STDOUT_FILENO, "\n");
        return EXIT_SUCCESS;
    } else {
        writestr(STDOUT_FILENO, "Proxying command to main process\n");
        return EXIT_SUCCESS;
    }
}

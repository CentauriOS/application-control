#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <appctl-rpc/wrapper.h>

int main(int argc, const char **argv) {
    if (argc == 4 && strcmp(argv[1], "wrap") == 0) {
        if (wrap(argv[0], argv[2], argv[3]) < 0) {
            perror("Unable to create process wrapper");
            return EXIT_FAILURE;
        } else {
            puts("Successfully created process wrapper");
            return EXIT_SUCCESS;
        }
    } else if (is_process_wrapper()) {
        printf("Launching process %s in container %s\n", get_process_wrapper_path(), get_process_wrapper_container());
        return EXIT_SUCCESS;
    } else {
        puts("Proxying command to main process");
        return EXIT_SUCCESS;
    }
}

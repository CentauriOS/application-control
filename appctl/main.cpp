#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace std;
using namespace centauri::appctl::common;

int main(int argc, const char **argv) {
    options_t options(argc - 1, argv + 1);
    if (errno != 0) {
        cerr << "Unable to parse arguments: " << strerror(errno) << endl;
        return EXIT_FAILURE;
    }
    if (options.helpRequested()) {
        cerr << "Function not implemented" << endl;
        return EXIT_FAILURE;
    } else {
        errno = options.getCommandInstance()->run(options.getCommandOptions());
        if (errno != 0) {
            cerr << "Error running command: " << strerror(errno) << endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
#include <appctl/log.hpp>
using namespace centauri::appctl;
using namespace centauri::appctl::common;

int main(int argc, const char **argv) {
    options_t options(argc - 1, argv + 1);
    if (errno != 0) {
        log::error(LOG_EMERG, "Unable to parse arguments: %s");
        return EXIT_FAILURE;
    }
    log::setVerbosity(options.getLoggingVerbosity());
    if (options.helpRequested()) {
        errno = ENOSYS;
        log::error(LOG_CRIT, "Unable to show help: %s");
        return EXIT_FAILURE;
    } else {
        errno = options.getCommandInstance()->run(options.getCommandOptions());
        if (errno != 0) {
            log::error(LOG_CRIT, "Error running command: %s");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

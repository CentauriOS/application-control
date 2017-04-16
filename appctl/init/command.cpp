#include <unistd.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
#include <appctl/log.hpp>
using namespace centauri::appctl::common;

namespace centauri {
    namespace appctl {
        namespace init {
            int command::run(commandOptions_t *options) {
                log::prompt("Hello, world!");
                sleep(5);
                return 0;
            }
        }
    }
}

#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::restartOpts_t;

namespace centauri {
    namespace appctl {
        namespace restart {
            int command::run(commandOptions_t *_options) {
                restartOpts_t *options = (restartOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

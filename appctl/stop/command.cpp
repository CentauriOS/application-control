#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::stopOpts_t;

namespace centauri {
    namespace appctl {
        namespace stop {
            int command::run(commandOptions_t *_options) {
                stopOpts_t *options = (stopOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

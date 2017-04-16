#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::reloadOpts_t;

namespace centauri {
    namespace appctl {
        namespace reload {
            int command::run(commandOptions_t *_options) {
                reloadOpts_t *options = (reloadOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

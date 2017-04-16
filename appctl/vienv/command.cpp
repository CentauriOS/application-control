#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::vienvOpts_t;

namespace centauri {
    namespace appctl {
        namespace vienv {
            int command::run(commandOptions_t *_options) {
                vienvOpts_t *options = (vienvOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

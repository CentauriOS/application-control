#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::autostartOpts_t;

namespace centauri {
    namespace appctl {
        namespace autostart {
            int command::run(commandOptions_t *_options) {
                autostartOpts_t *options = (autostartOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

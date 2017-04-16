#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::invokeOpts_t;

namespace centauri {
    namespace appctl {
        namespace invoke {
            int command::run(commandOptions_t *_options) {
                invokeOpts_t *options = (invokeOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

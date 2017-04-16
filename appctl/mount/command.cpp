#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::mountOpts_t;

namespace centauri {
    namespace appctl {
        namespace mount {
            int command::run(commandOptions_t *_options) {
                mountOpts_t *options = (mountOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::startOpts_t;

namespace centauri {
    namespace appctl {
        namespace start {
            int command::run(commandOptions_t *_options) {
                startOpts_t *options = (startOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

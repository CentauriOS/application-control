#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::shutdownOpts_t;

namespace centauri {
    namespace appctl {
        namespace shutdown {
            int command::run(commandOptions_t *_options) {
                shutdownOpts_t *options = (shutdownOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

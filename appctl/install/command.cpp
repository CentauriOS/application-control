#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::installOpts_t;

namespace centauri {
    namespace appctl {
        namespace install {
            int command::run(commandOptions_t *_options) {
                installOpts_t *options = (installOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

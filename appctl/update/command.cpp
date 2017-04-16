#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::updateOpts_t;

namespace centauri {
    namespace appctl {
        namespace update {
            int command::run(commandOptions_t *_options) {
                updateOpts_t *options = (updateOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

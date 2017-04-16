#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::pushfOpts_t;

namespace centauri {
    namespace appctl {
        namespace pushf {
            int command::run(commandOptions_t *_options) {
                pushfOpts_t *options = (pushfOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

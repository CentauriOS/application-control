#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::createOpts_t;

namespace centauri {
    namespace appctl {
        namespace create {
            int command::run(commandOptions_t *_options) {
                createOpts_t *options = (createOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

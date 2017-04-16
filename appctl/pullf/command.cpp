#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::pullfOpts_t;

namespace centauri {
    namespace appctl {
        namespace pullf {
            int command::run(commandOptions_t *_options) {
                pullfOpts_t *options = (pullfOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

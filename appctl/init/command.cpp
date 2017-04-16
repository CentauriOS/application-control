#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::initOpts_t;

namespace centauri {
    namespace appctl {
        namespace init {
            int command::run(commandOptions_t *_options) {
                initOpts_t *options = (initOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

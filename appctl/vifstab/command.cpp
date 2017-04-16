#include <errno.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace centauri::appctl::common;
using centauri::appctl::common::commands::vifstabOpts_t;

namespace centauri {
    namespace appctl {
        namespace vifstab {
            int command::run(commandOptions_t *_options) {
                vifstabOpts_t *options = (vifstabOpts_t *) _options;
                return ENOSYS;
            }
        }
    }
}

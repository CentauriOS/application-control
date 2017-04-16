#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
using namespace std;
using namespace centauri::appctl::common;

namespace centauri {
    namespace appctl {
        namespace init {
            int command::run(commandOptions_t *options) {
                cerr << "Hello, world!" << endl;
                sleep(5);
                return 0;
            }
        }
    }
}

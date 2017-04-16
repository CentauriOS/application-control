#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <appctl/options.hpp>
#include <appctl/commands.hpp>
#include <appctl/init/initsock.hpp>
using namespace std;
using namespace centauri::appctl::common;

namespace centauri {
    namespace appctl {
        namespace init {
            int command::run(commandOptions_t *options) {
                sleep(1);
                initsock_t sock;
                cerr << "Hello, world!" << endl;
                sleep(5);
                sock.shutdown();
                return 0;
            }
        }
    }
}

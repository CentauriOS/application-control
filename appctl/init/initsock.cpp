#include <cstring>
#include <errno.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <common/paths.h>
#include <appctl/init/initsock.hpp>
using namespace std;

namespace centauri {
    namespace appctl {
        namespace init {
            initsock::initsock() {
                if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
                    cerr << "Unable to open socket: " << strerror(errno) << endl;
                } else {
                    struct sockaddr_un addr;
                    memset(&addr, 0, sizeof(addr));
                    addr.sun_family = AF_UNIX;
                    strcpy(addr.sun_path, CONTROL_SOCKET_PATH);
                    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
                        cerr << "Unable to connect to socket: " << strerror(errno) << endl;
                    }
                }
            }

            void initsock::shutdown() {
                close(fd);
            }
        }
    }
}

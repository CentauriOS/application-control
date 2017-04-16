#ifndef CENTAURI_INITSOCK_HPP
#define CENTAURI_INITSOCK_HPP

namespace centauri {
    namespace appctl {
        namespace init {
            class initsock {
                public:
                    initsock();
                    void shutdown();
                
                private:
                    int fd;
            };
            typedef class initsock initsock_t;
        }
    }
}

#endif

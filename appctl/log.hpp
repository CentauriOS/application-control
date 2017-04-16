#ifndef CENTAURI_LOG_HPP
#define CENTAURI_LOG_HPP
#include <syslog.h>

namespace centauri {
    namespace appctl {
        namespace log {
            void error(int priority, const char *format);
            void format(int priority, const char *format, ...);
            void write(int priority, const char *msg);
            void prompt(const char *msg);
            void promptFormat(const char *format, ...);
            void setVerbosity(int verbosity);
        }
    }
}

#endif

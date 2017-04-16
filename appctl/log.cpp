#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <syslog.h>
#include <appctl/log.hpp>

namespace centauri {
    namespace appctl {
        namespace log {
            int verbosity;

            FILE *getStream(int priority);

            void error(int priority, const char *format) {
                const char *str = strerror(errno);
                syslog(priority, format, str);
                FILE *stream = getStream(priority);
                if (stream != NULL) {
                    fprintf(stream, format, str);
                    fprintf(stream, "\n");
                }
            }

            void format(int priority, const char *format, ...) {
                va_list args;
                va_start(args, format);
                vsyslog(priority, format, args);
                FILE *stream = getStream(priority);
                if (stream != NULL) {
                    vfprintf(stream, format, args);
                    fprintf(stream, "\n");
                }
            }

            void write(int priority, const char *msg) {
                syslog(priority, "%s", msg);
                FILE *stream = getStream(priority);
                if (stream != NULL) {
                    fputs(msg, stream);
                }
            }

            void prompt(const char *msg) {
                puts(msg);
            }

            void promptFormat(const char *format, ...) {
                va_list args;
                va_start(args, format);
                vprintf(format, args);
            }

            void setVerbosity(int _verbosity) {
                verbosity = _verbosity;
                closelog();
                openlog("appctl", LOG_NDELAY, LOG_DAEMON);
            }

            FILE *getStream(int priority) {
                switch (priority) {
                    case LOG_EMERG:
                    case LOG_ALERT:
                    case LOG_CRIT:
                    case LOG_ERR:
                        return stderr;
                    case LOG_WARNING:
                        return verbosity > 0 ? stderr : NULL;
                    case LOG_NOTICE:
                    case LOG_INFO:
                        return verbosity > 1 ? stdout : NULL;
                    case LOG_DEBUG:
                        return verbosity > 2 ? stdout : NULL;
                    default:
                        return NULL;
                }
            }
        }
    }
}

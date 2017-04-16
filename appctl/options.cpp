#include <cstring>
#include <errno.h>
#include <iostream>
#include <appctl/commands.hpp>
#include <appctl/options.hpp>
using namespace std;
using namespace centauri::appctl::common::commands;

namespace centauri {
    namespace appctl {
        namespace common {
            namespace commands {
                int autostartOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int createOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int initOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int installOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int invokeOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int mountOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int pullfOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int pushfOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int reloadOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int restartOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int shutdownOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int startOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int stopOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int updateOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int vienvOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }

                int vifstabOpts::load(int argc, const char **argv) {
                    return ENOSYS;
                }
            }

            options::options(int argc, const char **argv) : globalOptions(0), commandOptions(NULL) {
                bool overlyVerbose = false;
                int i;
                for (i = 0; i < argc; ++i) {
                    // Parse global options
                    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                        globalOptions |= GLOBAL_OPTION_HELP;
                        if (i + 1 < argc && *argv[i + 1] != '-') {
                            command = argv[++i];
                        }
                    } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
                        if ((globalOptions & GLOBAL_OPTION_VERBOSE) == GLOBAL_OPTION_VERBOSE) {
                            if (!overlyVerbose) {
                                cerr << "Too many " << argv[i] << " options (ignoring the rest)" << endl;
                                overlyVerbose = true;
                            }
                        } else {
                            globalOptions += GLOBAL_OPTION_LOG;
                        }
                    }
                    // Parse commands
#define CMD(name, value, cls, cmd) \
                    else if (strcmp(argv[i], name) == 0) { \
                        command = argv[i++]; \
                        commandOptions = new class cls(); \
                        commandObj = new class cmd(); \
                        break; \
                    }
#define CONCAT(a, b) a ## b
#define STR(a) # a
#define COMMAND(lower, upper) CMD(STR(lower), CONCAT(COMMAND_, upper), CONCAT(lower, Opts), lower::command)
                    COMMAND(autostart, AUTOSTART)
                    COMMAND(create, CREATE)
                    COMMAND(init, INIT)
                    COMMAND(install, INSTALL)
                    COMMAND(invoke, INVOKE)
                    COMMAND(mount, MOUNT)
                    COMMAND(pullf, PULLF)
                    COMMAND(pushf, PUSHF)
                    COMMAND(reload, RELOAD)
                    COMMAND(restart, RESTART)
                    COMMAND(shutdown, SHUTDOWN)
                    COMMAND(start, START)
                    COMMAND(stop, STOP)
                    COMMAND(update, UPDATE)
                    COMMAND(vienv, VIENV)
                    COMMAND(vifstab, VIFSTAB)
#undef CMD
#undef CONCAT
#undef STR
#undef COMMAND
                    // Handle unknown arguments
                    else {
                        cerr << "Unable to parse " << argv[i] << endl;
                        globalOptions = GLOBAL_OPTION_HELP;
                        command = NULL;
                        commandOptions = NULL;
                        errno = EINVAL;
                        break;
                    }
                }
                if (commandOptions == NULL) {
                    if ((globalOptions & GLOBAL_OPTION_HELP) == 0) {
                        cerr << "No command found" << endl;
                        globalOptions = GLOBAL_OPTION_HELP;
                        errno = EINVAL;
                    } else {
                        errno = 0;
                    }
                } else {
                    errno = commandOptions->load(argc - i, argv + i);
                }
            }

            bool options::helpRequested() {
                return (globalOptions & GLOBAL_OPTION_HELP) != 0;
            }

            const char *options::getCommand() {
                return command;
            }

            commandOptions_t *options::getCommandOptions() {
                return commandOptions;
            }

            command_t *options::getCommandInstance() {
                return commandObj;
            }
        }
    }
}

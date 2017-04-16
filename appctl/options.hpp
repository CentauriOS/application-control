#ifndef CENTAURI_OPTIONS_HPP
#define CENTAURI_OPTIONS_HPP

#define GLOBAL_OPTION_HELP     0x00000001
#define GLOBAL_OPTION_LOG      0x00000002 // ...01.
#define GLOBAL_OPTION_DEBUG    0x00000004 // ...10.
#define GLOBAL_OPTION_VERBOSE  0x00000006 // ...11.

namespace centauri {
    namespace appctl {
        namespace common {
            class options;

            class commandOptions {
                friend class options;

                protected:
                    virtual int load(int argc, const char **argv) = 0;
            };
            typedef class commandOptions commandOptions_t;

            namespace commands {
                class autostartOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class autostartOpts autostartOpts_t;

                class createOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class createOpts createOpts_t;

                class initOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class initOpts initOpts_t;

                class installOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class installOpts installOpts_t;

                class invokeOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class invokeOpts invokeOpts_t;

                class mountOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class mountOpts mountOpts_t;

                class pullfOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class pullfOpts pullfOpts_t;

                class pushfOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class pushfOpts pushfOpts_t;

                class reloadOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class reloadOpts reloadOpts_t;

                class restartOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class restartOpts restartOpts_t;

                class shutdownOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class shutdownOpts shutdownOpts_t;

                class startOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class startOpts startOpts_t;

                class stopOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class stopOpts stopOpts_t;

                class updateOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class updateOpts updateOpts_t;

                class vienvOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class vienvOpts vienvOpts_t;

                class vifstabOpts : public commandOptions {
                    protected:
                        int load(int argc, const char **argv);
                };
                typedef class vifstabOpts vifstabOpts_t;
            }

            class command;
            typedef class command command_t;

            class options {
                public:
                    options(int argc, const char **argv);
                    bool helpRequested();
                    const char *getCommand();
                    commandOptions_t *getCommandOptions();
                    command_t *getCommandInstance();
                
                private:
                    int globalOptions;
                    const char *command;
                    commandOptions_t *commandOptions;
                    command_t *commandObj;
            };
            typedef class options options_t;
        }
    }
}

#endif

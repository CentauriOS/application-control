#ifndef CENTAURI_COMMANDS_HPP
#define CENTAURI_COMMANDS_HPP

namespace centauri {
    namespace appctl {
        namespace common {
            class commandOptions;
            typedef class commandOptions commandOptions_t;

            class command {
                public:
                    virtual int run(commandOptions_t *options) = 0;
            };
            typedef class command command_t;
        }

        namespace autostart {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace create {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace init {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace install {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace invoke {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace mount {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace pullf {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace pushf {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace reload {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace restart {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace shutdown {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace start {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace stop {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace update {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace vienv {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }

        namespace vifstab {
            class command : public common::command {
                public:
                    int run(common::commandOptions_t *options);
            };
        }
    }
}

#endif

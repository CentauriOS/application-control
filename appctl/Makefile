OBJS = main.o options.o autostart/command.o create/command.o init/command.o install/command.o invoke/command.o mount/command.o pullf/command.o pushf/command.o reload/command.o restart/command.o shutdown/command.o start/command.o stop/command.o update/command.o vienv/command.o vifstab/command.o
LDFLAGS += -static
CFLAGS += -I..
CXXFLAGS += -I..

.PHONY: all
all: appctl

appctl: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS) appctl

main.cpp: commands.hpp options.hpp

options.cpp: commands.hpp options.hpp

autostart/command.o: commands.hpp options.hpp

create/command.o: commands.hpp options.hpp

init/command.o: commands.hpp options.hpp

install/command.o: commands.hpp options.hpp

invoke/command.o: commands.hpp options.hpp

mount/command.o: commands.hpp options.hpp

pullf/command.o: commands.hpp options.hpp

pushf/command.o: commands.hpp options.hpp

reload/command.o: commands.hpp options.hpp

restart/command.o: commands.hpp options.hpp

shutdown/command.o: commands.hpp options.hpp

start/command.o: commands.hpp options.hpp

stop/command.o: commands.hpp options.hpp

update/command.o: commands.hpp options.hpp

vienv/command.o: commands.hpp options.hpp

vifstab/command.o: commands.hpp options.hpp

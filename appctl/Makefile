OBJS = main.o
LDFLAGS += -static

.PHONY: all
all: appctl

appctl: $(OBJS)
	$(CXX) -o $@ $< $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS) appctl

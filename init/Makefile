OBJS = main.o
LDFLAGS += -static

.PHONY: all
all: init initrd.img

init: $(OBJS)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

initrd.img: init
	echo $< | cpio -o -H newc | gzip > $@

.PHONY: clean
clean:
	rm -f $(OBJS) init initrd.img

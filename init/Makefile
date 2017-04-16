OBJS = main.o fs.o net.o proc.o
LDFLAGS += -static
CFLAGS += -I..

.PHONY: all
all: init initrd.img

init: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

initrd.img: initrd.img.txt $(shell cat initrd.img.txt)
	cpio -o -H newc < $< | gzip > $@

.PHONY: clean
clean:
	rm -f $(OBJS) init initrd.img

fs.o: fs.h ../common/paths.h

main.o: fs.h net.h proc.h ../common/paths.h

net.o: net.h ../common/paths.h

proc.o: proc.h

OBJS = main.o wrapper.o string.o errno.o substart.o syscall.o
CFLAGS += -I.. -Os -nostdlib

.PHONY: all
all: appctl

appctl: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)
	dd if=/dev/zero of=$@ bs=1 count=1 seek=$$(($$(printf "%d" 0x$$(nm -g $@ | grep "container_name$$" | cut -d" " -f1))-6291456)) conv=notrunc
	dd if=/dev/zero of=$@ bs=1 count=1 seek=$$(($$(printf "%d" 0x$$(nm -g $@ | grep "process_path$$" | cut -d" " -f1))-6291456)) conv=notrunc
	printf "%08X" $$(($$(printf "%d" 0x$$(nm -g appctl | grep "container_name$$" | cut -d" " -f1))-6291456)) | grep -o .. | tac | echo "$$(tr -d '\n')" | xxd -r -p | dd of=$@ bs=1 count=4 seek=$$(($$(printf "%d" 0x$$(nm -g $@ | grep "container_name_offset$$" | cut -d" " -f1))-6291456)) conv=notrunc
	printf "%08X" $$(($$(printf "%d" 0x$$(nm -g appctl | grep "process_path$$" | cut -d" " -f1))-6291456)) | grep -o .. | tac | echo "$$(tr -d '\n')" | xxd -r -p | dd of=$@ bs=1 count=4 seek=$$(($$(printf "%d" 0x$$(nm -g $@ | grep "process_path_offset$$" | cut -d" " -f1))-6291456)) conv=notrunc

.PHONY: clean
clean:
	rm -f $(OBJS) appctl

main.o: wrapper.h string.h

wrapper.o: wrapper.h string.h ../common/limits.h

string.o: string.h

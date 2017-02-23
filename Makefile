KERNEL=../kernel/linux/arch/x86/boot/bzImage

.PHONY: all
all: appctl/appctl init/init init/initrd.img

appctl/appctl:
	$(MAKE) -C common all
	$(MAKE) -C appctl appctl

init/init:
	$(MAKE) -C common all
	$(MAKE) -C init init

init/initrd.img:
	$(MAKE) -C common all
	$(MAKE) -C init initrd.img

.PHONY: clean
clean:
	$(MAKE) -C appctl clean
	$(MAKE) -C common clean
	$(MAKE) -C init clean

.PHONY: run
run: init/initrd.img
	qemu-system-x86_64 -kernel $(KERNEL) -initrd $< -nographic -append "console=ttyS0" | tee serial.log

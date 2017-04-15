KERNEL=../kernel/linux/arch/x86/boot/bzImage
RECOVERY_SIZE = 512M
SUDO = sudo

.PHONY: all
all: appctl/appctl init/init init/initrd.img

appctl/appctl: always
	$(MAKE) -C common all
	$(MAKE) -C appctl appctl

init/init: always
	$(MAKE) -C common all
	$(MAKE) -C init init

init/initrd.img: always
	$(MAKE) -C common all
	$(MAKE) -C init initrd.img

.PHONY: clean
clean:
	$(MAKE) -C appctl clean
	$(MAKE) -C common clean
	$(MAKE) -C init clean
	rm -rf recovery.iso

.PHONY: always
always:

.PHONY: run
run: init/initrd.img recovery.iso
	qemu-system-x86_64 -kernel $(KERNEL) -initrd $< -nographic -append "console=ttyS0" -drive "format=raw,file=recovery.iso" | tee serial.log

recovery.iso:
	fallocate -l $(RECOVERY_SIZE) $@
	mkfs.ext4 $@
	mkdir -p mnt
	$(SUDO) mount $@ mnt
	$(SUDO) debootstrap jessie mnt || ($(SUDO) umount mnt && false)
	$(SUDO) ln -s /bin/bash mnt/sbin/recover || ($(SUDO) umount mnt && false)
	$(SUDO) umount mnt

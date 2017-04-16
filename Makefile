KERNEL=../kernel/linux/arch/x86/boot/bzImage
RECOVERY_SIZE = 512M
DISK_SIZE = 2G
SUDO = sudo

.PHONY: all
all: appctl/appctl init/init init/initrd.img recover/recover recovery.iso disk.iso

appctl/appctl: always
	$(MAKE) -C common all
	$(MAKE) -C appctl appctl

init/init: always
	$(MAKE) -C common all
	$(MAKE) -C init init

init/initrd.img: always
	$(MAKE) -C common all
	$(MAKE) -C init initrd.img

recover/recover: always
	$(MAKE) -C common all
	$(MAKE) -C recover all

.PHONY: clean
clean:
	$(MAKE) -C appctl clean
	$(MAKE) -C common clean
	$(MAKE) -C init clean
	$(MAKE) -C recover clean
	rm -rf recovery.iso disk.iso

.PHONY: always
always:

.PHONY: run
run: init/initrd.img recovery.iso disk.iso
	$(SUDO) qemu-system-x86_64 -kernel $(KERNEL) -initrd $< -nographic -append "console=ttyS0" -drive "format=raw,file=recovery.iso" -drive "format=raw,file=disk.iso" | tee serial.log

recovery.iso: always recover/recover
	mkdir -p mnt
	[ -f $@ ] || (fallocate -l $(RECOVERY_SIZE) $@ && mkfs.ext4 $@)
	$(SUDO) mount $@ mnt
	$(SUDO) $(MAKE) -C mnt -f ../recovery.iso.mk || ($(SUDO) umount mnt && false)
	$(SUDO) umount mnt

disk.iso: always appctl/appctl
	mkdir -p mnt
	[ -f $@ ] || (fallocate -l $(DISK_SIZE) $@ && mkfs.ext4 $@)
	$(SUDO) mount $@ mnt
	$(SUDO) $(MAKE) -C mnt -f ../disk.iso.mk || ($(SUDO) umount mnt && false)
	$(SUDO) umount mnt

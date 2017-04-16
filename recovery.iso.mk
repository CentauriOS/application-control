all: etc/debian_version sbin/recover

etc/debian_version:
	debootstrap jessie .

sbin/recover: ../recover/recover
	mkdir -p sbin
	cp -f $< $@

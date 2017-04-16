all: data/com.github.centaurios.application-control/bin/appctl dev proc tmp sys

dev:
	mkdir -p dev

proc:
	mkdir -p proc

tmp:
	mkdir -p tmp

sys:
	mkdir -p sys

data/com.github.centaurios.application-control/bin/appctl: ../appctl/appctl
	mkdir -p data/com.github.centaurios.application-control/bin
	cp -f $< $@

all: data/com.github.centaurios.application-control/bin/appctl dev proc tmp sys data/com.github.centaurios.application-control/tmp

dev:
	mkdir -p $@

proc:
	mkdir -p $@

tmp:
	mkdir -p $@

sys:
	mkdir -p $@

data/com.github.centaurios.application-control/bin/appctl: ../appctl/appctl
	mkdir -p data/com.github.centaurios.application-control/bin
	cp -f $< $@

data/com.github.centaurios.application-control/tmp:
	mkdir -p $@

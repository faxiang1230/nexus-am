include Makefile.check

AM_HOME ?= $(shell pwd)

default:
	@$(MAKE) -s -C am

# clean everything
ALLMAKE = $(dir $(shell find . -mindepth 2 -name "Makefile"))
$(ALLMAKE):
	-@$(MAKE) -s -C $@ clean

dirs:= tests/cputest tests/amtest tests/aliastest tests/bitmanip tests/dualcoretest
dirs += tests/cacheoptest/dcache tests/cacheoptest/icache tests/cacheoptest/llc tests/crypto
dirs += apps/coremark apps/loader apps/dhrystone apps/hello
.PHONY:$(dirs) build
$(dirs):
	make -C $@ test

build:
	@for dir in $(dirs);\
	do $(MAKE) -C $$dir -j1; \
	done
test:$(dirs)

clean: $(ALLMAKE)

.PHONY: default clean $(ALLMAKE)

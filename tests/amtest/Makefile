NAME := amtest
SRCS := $(shell find -L ./src/ -name "*.[cS]")

include $(AM_HOME)/Makefile.app

test_args=c s i e x r

test: $(addprefix Makefile-, $(test_args))

$(test_args): %: Makefile-%

Makefile-%: % force
ifeq ($*,x)
	@/bin/echo -e "NAME = ${NAME}-$*\nSRCS = ${SRCS}\nmainargs=$*\nDUAL_EMU += --nodiff\nSINGLE_EMU=DUAL_EMU\nARCH=riscv64-xs-southlake\n\nLIBS += klib\ninclude $${AM_HOME}/Makefile.app" > $@
else
ifeq ($*,r)
	@/bin/echo -e "NAME = ${NAME}-$*\nSRCS = ${SRCS}\nmainargs=$*\nDUAL_EMU += --nodiff\nARCH=riscv64-xs-southlake\n\nLIBS += klib\ninclude $${AM_HOME}/Makefile.app" > $@
else
	@/bin/echo -e "NAME = ${NAME}-$*\nSRCS = ${SRCS}\nmainargs=$*\nARCH=riscv64-xs-southlake\n\nLIBS += klib\ninclude $${AM_HOME}/Makefile.app" > $@
endif
endif
	@make -f $@ test
force:;

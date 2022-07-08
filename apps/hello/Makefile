NAME = hello
SRCS = hello.c
include $(AM_HOME)/Makefile.app
test_arch=riscv64-xs-southlake riscv64-xs-southlake-flash riscv64-xs

test: $(addprefix Makefile., $(test_arch))

$(test_arch): %: Makefile.%

Makefile.%: % force
	@/bin/echo -e "NAME = ${NAME}\nSRCS = ${SRCS}\nLIBS += klib\ninclude $${AM_HOME}/Makefile.app" > $@
	@make -f $@ ARCH=$< test
force:;

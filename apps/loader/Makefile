NAME = flash-loader
SRCS = main.c image.S
ELF_PATH ?= ./image/coremark-riscv64-xs.bin
ASFLAGS += -DELF_PATH=\"$(ELF_PATH)\"

ARCH=riscv64-xs-southlake-flash
ELF_PATH=./image/coremark-riscv64-xs-southlake.bin

image.S: $(ELF_PATH)
	touch image.S

include $(AM_HOME)/Makefile.app

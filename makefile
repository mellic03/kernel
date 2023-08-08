INCLUDES     =  -I./src/include/libc    -I./src/include/libc++    -I./src/include/limine
LIBINCLUDES  =  -L./src/lib/libc		-L./src/lib/libc++

INC = $(INCLUDES) $(LIBINCLUDES)


# Nuke built-in rules and variables.
override MAKEFLAGS += -rR
 
# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := myos.elf
 
# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef
 
# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
override DEFAULT_CXX := g++
$(eval $(call DEFAULT_VAR,CXX,$(DEFAULT_CXX)))
 
# Same thing for "ld" (the linker).
override DEFAULT_LD := ld
$(eval $(call DEFAULT_VAR,LD,$(DEFAULT_LD)))
 
# User controllable C flags.
override DEFAULT_CFLAGS := -g -O2 -pipe
$(eval $(call DEFAULT_VAR,CFLAGS,$(DEFAULT_CFLAGS)))
 
# User controllable C preprocessor flags. We set none by default.
override DEFAULT_CPPFLAGS :=
$(eval $(call DEFAULT_VAR,CPPFLAGS,$(DEFAULT_CPPFLAGS)))
 
# User controllable nasm flags.
override DEFAULT_NASMFLAGS := -F dwarf -g
$(eval $(call DEFAULT_VAR,NASMFLAGS,$(DEFAULT_NASMFLAGS)))
 
# User controllable linker flags. We set none by default.
override DEFAULT_LDFLAGS :=
$(eval $(call DEFAULT_VAR,LDFLAGS,$(DEFAULT_LDFLAGS)))
 
# Internal C flags that should not be changed by the user.
override CFLAGS += \
    -Wextra \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -m64 \
    -march=x86-64 \
    -mabi=sysv \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone
 
# Internal C preprocessor flags that should not be changed by the user.
override CPPFLAGS := \
    -I. \
    -std=c++17 \
    -MMD \
    -MP
 
# Internal linker flags that should not be changed by the user.
override LDFLAGS += \
    -m elf_x86_64 \
    -nostdlib \
    -static \
    -pie \
    --no-dynamic-linker \
    -z text \
    -z max-page-size=0x1000 \
    -T linker.ld
 
# Internal nasm flags that should not be changed by the user.
override NASMFLAGS += \
    -Wall \
    -f elf64
 
# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
override CPPFILES := $(shell find -L . -type f -name '*.cpp' | grep -v 'limine/')
override ASFILES := $(shell find -L . -type f -name '*.S' | grep -v 'limine/')
override NASMFILES := $(shell find -L . -type f -name '*.asm' | grep -v 'limine/')
override OBJ := $(CPPFILES:.cpp=.cpp.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o)
override HEADER_DEPS := $(CPPFILES:.cpp=.cpp.d) $(ASFILES:.S=.S.d)
 
# Default target.
.PHONY: all
all: $(KERNEL)
 
# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@
 
# Include header dependencies.
-include $(HEADER_DEPS)
 
# Compilation rules for *.cpp files.
%.cpp.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(INC) -c $< -o $@
 
# Compilation rules for *.S files.
%.S.o: %.S
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(INC) -c $< -o $@
 
# Compilation rules for *.asm (nasm) files.
%.asm.o: %.asm
	nasm $(NASMFLAGS) $(INC) $< -o $@
 
# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)
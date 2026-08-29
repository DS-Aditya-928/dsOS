OUTLIB = libk.a

CXXFLAGS := -g -ffreestanding -Wall -Wextra -mtext-section-literals -mlongcalls -mabi=call0 -nostdlib -nostdinc

INC_FLAGS := -I ./include
CPPFLAGS := $(INC_FLAGS)

BUILD_DIR := build

C_SRCS := $(wildcard *.c)
S_SRCS   := $(wildcard *.S)

C_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS))
S_OBJS   := $(patsubst %.S,$(BUILD_DIR)/%.o,$(S_SRCS))
OBJS     := $(C_OBJS) $(S_OBJS)

.PHONY: all clean

all: $(OUTLIB)

$(OUTLIB): $(OBJS) makefile
	clang-format -i -style="{BasedOnStyle: WebKit, BreakBeforeBraces: Allman}" $(wildcard *.c  include/*.h)
	xtensa-esp32-elf-ar rcs $@ $(OBJS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	xtensa-esp32-elf-gcc -MD -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	xtensa-esp32-elf-gcc -MD -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(OUTLIB)

rebuild: clean all

-include $(OBJS:.o=.d)
OUTLIB = libos.a

CXXFLAGS := -g -ffreestanding -Wall -Wextra -mtext-section-literals -mlongcalls -mabi=call0 -nostdlib -nostdinc

FOUND_INCLUDES := $(wildcard include ../*/include)
INC_FLAGS := $(addprefix -I, $(FOUND_INCLUDES))
CPPFLAGS := $(INC_FLAGS)

BUILD_DIR := build

CPP_SRCS := $(wildcard *.cpp */*.cpp)
S_SRCS   := $(wildcard *.S */*.S)

CPP_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
S_OBJS   := $(patsubst %.S,$(BUILD_DIR)/%.o,$(S_SRCS))
OBJS     := $(CPP_OBJS) $(S_OBJS)

.PHONY: all clean

all: $(OUTLIB)

$(OUTLIB): $(OBJS) makefile
	clang-format -i -style="{BasedOnStyle: WebKit, BreakBeforeBraces: Allman}" $(wildcard *.cpp  include/*.h)
	xtensa-esp32-elf-ar rcs $@ $(OBJS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	xtensa-esp32-elf-g++ -MD -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	xtensa-esp32-elf-g++ -MD -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(OUTLIB)

-include $(OBJS:.o=.d)
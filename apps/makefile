CXX = xtensa-esp32-elf-gcc
DISASM = xtensa-esp32-elf-objdump
MAKEFILE = makefile

APP_NAME = test
TARGET = $(APP_NAME).elf
CXXFLAGS = -mtext-section-literals -mabi=call0 -fno-exceptions -fno-builtin -nostdlib -nostartfiles -s -fno-ident

LDFLAGS = -Wl,-T linker.ld -Wl,-Map=sections.map -Wl,--nmagic

DISASM_FLAGS = -D -f -h -x -z -s -G -t

DEFAULT: $(TARGET)

SRCS = test.c

$(TARGET): $(SRCS) $(MAKEFILE)
	$(CXX) $(SRCS) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)
	$(DISASM) $(DISASM_FLAGS) $(TARGET) > $(TARGET).disasm

clean:
	rm -f *.o *.map *.elf *.disasm
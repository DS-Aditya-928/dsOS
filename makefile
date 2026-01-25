CXX = xtensa-esp32-elf-g++
DISASM = xtensa-esp32-elf-objdump
CONVERT = esptool.py
MAKEFILE = makefile

OS_SRCS = os/os.c++

TARGET = os.elf
TARGET_BIN = os.bin
CXXFLAGS = -mtext-section-literals -mabi=call0 -fno-exceptions -fno-builtin

INCLUDES = -Iinclude

LDIRS = -Llibhal -Llibc -Llibos
LIBS = -los -lhal -lk
LIBS_PATHS = libos/libos.a libhal/libhal.a libc/libk.a

LDFLAGS = -nostdlib -nostartfiles -Wl,-Tesp32/linker.ld

CHIP = esp32
FLASH_MODE = "dio"
FLASH_SIZE = "4MB"
FLASH_FREQ = "40m"

DISASM_FLAGS = -D -f

DEFAULT: $(TARGET)

build_libs:
	@for lib in $(LIBS_PATHS); do \
		echo "Building $$lib..."; \
		make -C $$(dirname $$lib); \
	done

$(TARGET): $(OS_SRCS) build_libs $(MAKEFILE)
	$(CXX) $(OS_SRCS) $(LDFLAGS) $(CXXFLAGS) $(INCLUDES) $(LDIRS) $(LIBS) -o $(TARGET)
	$(CONVERT) --chip $(CHIP) elf2image --flash_mode=$(FLASH_MODE) --flash_freq=$(FLASH_FREQ) --flash_size=$(FLASH_SIZE) -o $(TARGET_BIN) $(TARGET)
	$(DISASM) $(DISASM_FLAGS) $(TARGET) > $(TARGET).disasm

clean:
	rm -f $(TARGET) *.o
	rm -f $(TARGET_BIN)
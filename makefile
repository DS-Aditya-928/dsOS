CXX = xtensa-esp32-elf-g++
DISASM = xtensa-esp32-elf-objdump
CONVERT = esptool.py
MAKEFILE = makefile

OS_SRCS = os/os.c++

OS_NAME = dsOS
TARGET = $(OS_NAME).elf
TARGET_BIN = $(OS_NAME).bin
CXXFLAGS = -mtext-section-literals -mabi=call0 -fno-exceptions -fno-builtin -nostdlib -nostartfiles -nostdinc

FOUND_INCLUDES := $(wildcard include */include)
INCLUDES := $(addprefix -I, $(FOUND_INCLUDES))

LDIRS = -Llibhal -Llibk -Llibos
LIBS = -los -lhal -lk
LIBS_PATHS = libos/libos.a libhal/libhal.a libk/libk.a

LDFLAGS = -Wl,-T esp32/linker.ld -Wl,-Map=sections.map

CHIP = esp32
FLASH_MODE = dio
FLASH_SIZE = 8MB
FLASH_FREQ = 40m

DISASM_FLAGS = -D -f -h

DEFAULT: $(TARGET)

build_libs:
	@for lib in $(LIBS_PATHS); do \
		echo "Building $$lib..."; \
		make -C $$(dirname $$lib); \
	done

$(TARGET): $(OS_SRCS) build_libs $(MAKEFILE)
	$(CXX) $(OS_SRCS) $(LDFLAGS) $(CXXFLAGS) $(INCLUDES) $(LDIRS) $(LIBS) -o $(TARGET)
	$(CONVERT) --chip $(CHIP) elf2image --flash-mode=$(FLASH_MODE) --flash-freq=$(FLASH_FREQ) --flash-size=$(FLASH_SIZE) -o $(TARGET_BIN) $(TARGET)
	$(DISASM) $(DISASM_FLAGS) $(TARGET) > $(TARGET).disasm

clean-libs:
	@for lib in $(LIBS_PATHS); do \
		echo "Removing $$lib..."; \
		make -C $$(dirname $$lib) clean;\
	done

clean-main:
	rm -f *.o *.bin *.elf *.disasm

clean: clean-libs clean-main

flash: $(TARGET)
	esptool -p $(PORT) --before usb-reset --after hard-reset write-flash 0x1000 $(TARGET_BIN) 0x8000 __testFiles/dummy.bin 0x18000 __testFiles/dummy2.bin
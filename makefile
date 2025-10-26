CXX = xtensa-esp32-elf-g++
CONVERT = esptool.py

OS_SRCS = os/os.c++

TARGET = os.elf
TARGET_BIN = os.bin
CXXFLAGS = -mtext-section-literals -fno-exceptions -fno-builtin

INCLUDES = -Iinclude

LDIRS = -Llibhal -Llibc -Llibos
LIBS = -los -lhal -lk
LIBS_PATHS = libos/libos.a libhal/libhal.a libc/libk.a

LDFLAGS = -nostdlib -nostartfiles -Wl,-Tesp32/linker.ld

CHIP = esp32
FLASH_MODE = "dio"
FLASH_SIZE = "4MB"
FLASH_FREQ = "40m"

$(TARGET): $(OS_SRCS) $(LIBS_PATHS)
	$(CXX) $(OS_SRCS) $(LDFLAGS) $(CXXFLAGS) $(INCLUDES) $(LDIRS) $(LIBS) -o $(TARGET)
	$(CONVERT) --chip $(CHIP) elf2image --flash_mode=$(FLASH_MODE) --flash_freq=$(FLASH_FREQ) --flash_size=$(FLASH_SIZE) -o $(TARGET_BIN) $(TARGET)

clean:
	rm -f $(TARGET) *.o
	rm -f $(TARGET_BIN)
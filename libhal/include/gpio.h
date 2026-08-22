#pragma once

#include <stdbool.h>
#include <stdint.h>

class GPIO
{
public:
    static void setMode(uint8_t pin, uint8_t mode);
    static uint8_t getMode(uint8_t pin);
    static void write(uint8_t pin, uint8_t state);
    static uint8_t read(uint8_t pin);
};
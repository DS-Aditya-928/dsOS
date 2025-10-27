#pragma once

class GPIO
{
public:
    static void setMode(uint8_t pin, uint8_t mode);
    static void write(uint8_t pin, uint8_t state);
    static uint8_t read();
}
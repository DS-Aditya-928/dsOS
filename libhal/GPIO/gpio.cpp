#include "GPIO.h"

#define GPIO_BASE 0x3FF44000

#define GPIO_ENABLE_REG 0x20
#define GPIO_ENABLE_W1TS_REG 0x24
#define GPIO_ENABLE_W1TC_REG 0x28
#define GPIO_ENABLE1_REG 0x2C
#define GPIO_ENABLE1_W1TS_REG 0x30
#define GPIO_ENABLE1_W1TC_REG 0x34 

#define GPIO_OUT_W1TS_REG 0x08
#define GPIO_OUT_W1TC_REG 0x0C
#define GPIO_OUT1_W1TS_REG 0x14
#define GPIO_OUT1_W1TC_REG 0x18

#define GPIO_IN_REG 0x3C
#define GPIO_IN2_REG 0x0040

uint8_t GPIO::read(uint8_t pin)
{
    if(pin < 32)
    {
        uint32_t inReg = *(uint32_t*)(GPIO_BASE + GPIO_IN_REG);
        return (inReg >> pin) & 0x1;
    }
    else if(pin < 40)
    {
        uint32_t inReg = *(uint32_t*)(GPIO_BASE + GPIO_IN2_REG);
        return (inReg >> (pin - 32)) & 0x1;
    }

    return 0;
}

uint8_t GPIO::getMode(uint8_t pin)
{
    if(pin < 32)
    {
        uint32_t modeReg = *(uint32_t*)(GPIO_BASE + GPIO_ENABLE_REG);
        return (modeReg >> pin) & 0x1;
    }
    else if(pin < 40)
    {
        uint32_t modeReg = *(uint32_t*)(GPIO_BASE + GPIO_ENABLE1_REG);
        return (modeReg >> pin) & 0x1;
    }

    return 0;
}

void GPIO::setMode(uint8_t pin, uint8_t mode)
{
    if(pin < 32)
    {
        if(mode)
        {
            *(uint32_t*)(GPIO_BASE + GPIO_ENABLE_W1TS_REG) = (1 << pin);
        }
        else
        {
            *(uint32_t*)(GPIO_BASE + GPIO_ENABLE_W1TC_REG) = (1 << pin);
        }
    }
    else if(pin < 40)
    {
        if(mode)
        {
            *(uint32_t*)(GPIO_BASE + GPIO_ENABLE1_W1TS_REG) = (1 << (pin - 32));
        }

        else
        {
            *(uint32_t*)(GPIO_BASE + GPIO_ENABLE1_W1TC_REG) = (1 << (pin - 32));
        }
    }
}

void GPIO::write(uint8_t pin, uint8_t state)
{
    if(pin < 32)
    {
        if(state)
        {
            *(uint32_t*)(GPIO_BASE + GPIO_OUT_W1TS_REG) = (1 << pin);
        }
        else
        {
            *(uint32_t*)(GPIO_BASE + GPIO_OUT_W1TC_REG) = (1 << pin);
        }
    }

    else if(pin < 40)
    {
        if(state)
        {
            *(uint32_t*)(GPIO_BASE + GPIO_OUT1_W1TS_REG) = (1 << (pin - 32));
        }
        else
        {
            *(uint32_t*)(GPIO_BASE + GPIO_OUT1_W1TC_REG) = (1 << (pin - 32));
        }
    }
}
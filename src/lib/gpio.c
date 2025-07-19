#include "gpio.h"

#define GPIO_BASE 0xFE200000

// Register offsets
#define GPFSEL0_OFFSET 0x00
#define GPSET0_OFFSET 0x1C
#define GPSET1_OFFSET 0x20
#define GPCLR0_OFFSET 0x28
#define GPCLR1_OFFSET 0x2C

static volatile unsigned int *gpio_base = (volatile unsigned int *)GPIO_BASE;

void gpio_init(void)
{
	// placeholder for future initialization
}

void gpio_set_function(int pin, int function)
{
	int reg_index = pin / 10;				 // Which GPFSEL register
	int bit_offset = (pin % 10) * 3; // Bit position within register

	volatile unsigned int *reg = gpio_base + reg_index;
	unsigned int value = *reg;

	value &= ~(7 << bit_offset);			 // Clear 3 bits
	value |= (function << bit_offset); // Set function

	*reg = value;
}

void gpio_set(int pin)
{
	int reg_offset = (pin >= 32) ? GPSET1_OFFSET / 4 : GPSET0_OFFSET / 4;
	int bit = pin % 32;

	gpio_base[reg_offset] = (1 << bit);
}

void gpio_clear(int pin)
{
	int reg_offset = (pin >= 32) ? GPCLR1_OFFSET / 4 : GPCLR0_OFFSET / 4;
	int bit = pin % 32;

	gpio_base[reg_offset] = (1 << bit);
}

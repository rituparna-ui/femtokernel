#include "lib/gpio.h"

#define LED_PIN 42

void delay(int count)
{
	while (count-- > 0)
	{
		asm volatile("nop");
	}
}

void kernel_main()
{
	gpio_init();
	gpio_set_function(LED_PIN, GPIO_OUTPUT);

	while (1)
	{
		gpio_set(LED_PIN);
		delay(500000);
		gpio_clear(LED_PIN);
		delay(500000);
	}
}
#include "lib/gpio.h"
#include "lib/uart.h"

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
	// Initialize hardware
	gpio_init();
	uart_init();

	// Setup LED
	gpio_set_function(LED_PIN, GPIO_OUTPUT);

	uart_puts("Raspberry Pi - Femtokernel\n");

	int count = 0;
	while (1)
	{
		gpio_set(LED_PIN);
		uart_puts("LED ON\n");
		delay(1500000);

		gpio_clear(LED_PIN);
		uart_puts("LED OFF\n");
		delay(2500000);

		count++;
		if (count % 10 == 0)
		{
			uart_puts("Still alive...\n");
		}
	}
}

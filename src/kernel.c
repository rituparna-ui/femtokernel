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
	uart_puts("Echo Shell Ready!\n");
	uart_puts("You are on UART. Type something: ");

	gpio_set(LED_PIN);
	delay(500000);
	gpio_clear(LED_PIN);

	while (1)
	{
		char c = uart_getc();
		uart_putc(c);
	}
}
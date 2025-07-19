#define GPIO_BASE 0xFE200000
#define GPFSEL4 ((volatile unsigned int *)(GPIO_BASE + 0x10))
#define GPSET1 ((volatile unsigned int *)(GPIO_BASE + 0x20))
#define GPCLR1 ((volatile unsigned int *)(GPIO_BASE + 0x2C))

void delay(int count)
{
	while (count-- > 0)
	{
		asm volatile("nop");
	}
}

void kernel_main()
{
	// set GPIO 42 = output
	unsigned int ra = *GPFSEL4;
	ra &= ~(7 << 6); // Clear bits 6-8
	ra |= (1 << 6);	 // Set bit 6 (001 = output)
	*GPFSEL4 = ra;

	while (1)
	{
		*GPSET1 = (1 << 10); // GPIO 42 = bit 10 in SET1 register
		delay(500000);
		*GPCLR1 = (1 << 10); // GPIO 42 = bit 10 in CLR1 register
		delay(500000);
	}
}
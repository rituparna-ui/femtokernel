// Raspberry Pi 4 addresses
#define MMIO_BASE 0xFE000000
#define GPIO_BASE (MMIO_BASE + 0x200000)
#define UART0_BASE (MMIO_BASE + 0x201000)

// GPIO registers
#define GPFSEL1 (GPIO_BASE + 0x04)
#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

// UART registers
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)
#define UART0_IBRD (UART0_BASE + 0x24)
#define UART0_FBRD (UART0_BASE + 0x28)
#define UART0_LCRH (UART0_BASE + 0x2C)
#define UART0_CR (UART0_BASE + 0x30)
#define UART0_ICR (UART0_BASE + 0x44)

static inline void mmio_write(long reg, unsigned int val)
{
	*(volatile unsigned int *)reg = val;
}

static inline unsigned int mmio_read(long reg)
{
	return *(volatile unsigned int *)reg;
}

static inline void delay(long delay)
{
	asm volatile("__delay_%=: subs %[delay], %[delay], #1; bne __delay_%=\n"
							 : "=r"(delay) : [delay] "0"(delay) : "cc");
}

void uart_init()
{
	// Disable UART0
	mmio_write(UART0_CR, 0x00000000);

	// Setup GPIO pin 14 & 15
	unsigned int selector = mmio_read(GPFSEL1);
	selector &= ~(7 << 12); // Clean gpio14
	selector |= 4 << 12;		// Set alt0 for gpio14
	selector &= ~(7 << 15); // Clean gpio15
	selector |= 4 << 15;		// Set alt0 for gpio15
	mmio_write(GPFSEL1, selector);

	// Disable pull up/down for all GPIO pins & delay for 150 cycles
	mmio_write(GPPUD, 0x00000000);
	delay(150);

	// Disable pull up/down for pin 14,15 & delay for 150 cycles
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);

	// Write 0 to GPPUDCLK0 to make it take effect
	mmio_write(GPPUDCLK0, 0x00000000);

	// Clear pending interrupts
	mmio_write(UART0_ICR, 0x7FF);

	// Set integer & fractional part of baud rate
	// Divider = UART_CLOCK/(16 * Baud)
	// UART_CLOCK = 48000000; Baud = 115200
	// Divider = 48000000/(16 * 115200) = 26.041666667
	mmio_write(UART0_IBRD, 26);
	mmio_write(UART0_FBRD, 3);

	// Enable FIFO & 8 bit data transmission (1 stop bit, no parity)
	mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

	// Enable UART0, receive & transfer part of UART
	mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(unsigned char c)
{
	// Wait for UART to become ready to transmit
	while (mmio_read(UART0_FR) & (1 << 5))
	{
	}
	mmio_write(UART0_DR, c);
}

unsigned char uart_getc()
{
	// Wait for UART to have received something
	while (mmio_read(UART0_FR) & (1 << 4))
	{
	}
	return mmio_read(UART0_DR);
}

void uart_puts(const char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		uart_putc((unsigned char)str[i]);
	}
}

#ifndef GPIO_H
#define GPIO_H

void gpio_init(void);
void gpio_set_function(int pin, int function);
void gpio_set(int pin);
void gpio_clear(int pin);

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#endif

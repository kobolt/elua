#ifndef _PIO_H
#define _PIO_H

void pio_setup(void);
void pio_pin_set(int port, unsigned char pinmask);
void pio_pin_clear(int port, unsigned char pinmask);
unsigned char pio_pin_get(int port);

#endif /* _PIO_H */

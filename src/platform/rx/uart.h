#ifndef _UART_H
#define _UART_H

void uart0_setup(void);
void uart0_baud_setup(long int baud);
void uart0_send(char *s);
int uart0_recv(void);

#endif /* _UART_H */

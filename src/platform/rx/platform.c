#include "platform.h"
#include "type.h"
#include "uart.h"
#include "timer.h"
#include "pio.h"
#include "common.h"
#include "platform_conf.h"

int platform_init()
{
  asm("clrpsw i"); /* Disable interrupts */
  pio_setup();
  timer0_setup();
  uart0_setup();
  asm("setpsw i"); /* Enable interrupts */

  cmn_platform_init();

  return PLATFORM_OK;
} 

pio_type platform_pio_op(unsigned port, pio_type pinmask, int op)
{
  pio_type retval = 1;
  
  switch (op) {
  case PLATFORM_IO_PIN_SET:
    pio_pin_set(port, pinmask);
    break;
    
  case PLATFORM_IO_PIN_CLEAR:
    pio_pin_clear(port, pinmask);
    break;
    
  case PLATFORM_IO_PIN_GET:
    retval = pio_pin_get(port) & pinmask ? 1 : 0;
    break;
    
  default:
    retval = 0;
    break;
  }

  return retval;  
}

u32 platform_uart_setup(unsigned id, u32 baud, int databits, int parity, int stopbits)
{
  (void)id;
  (void)databits;
  (void)parity;
  (void)stopbits;

  /* Setting of databits, parity and stop is not implemented, always 8N1. */
  /* Only baudrates between 9600 and 38400 are reliable. */

  if (baud > 38400 || baud < 9600) {
    return PLATFORM_ERR;
  }

  uart0_baud_setup(baud); /* Only setting of new baud is supported. */
  return PLATFORM_OK;
}

void platform_s_uart_send(unsigned id, u8 data)
{
  (void)id;
  char send_data[2];

  send_data[0] = data;
  send_data[1] = '\0';
  uart0_send(send_data);
}

int platform_s_uart_recv(unsigned id, timer_data_type timeout)
{
  (void)id;
  int recv_data;

  if (timeout == 0) {
    return uart0_recv();
  }

  while (1) {
    recv_data = uart0_recv();
    if (recv_data != -1) {
      break;
    }
    asm("wait");
  }
  return recv_data;
}

int platform_s_uart_set_flow_control(unsigned id, int type)
{
  (void)id;
  (void)type;
  return PLATFORM_ERR;
}

void platform_s_timer_delay(unsigned id, timer_data_type delay_us)
{
  (void)id;

  timer0_set(delay_us / 1000);
  while (timer0_read() > 0) {
    asm("wait");
  }
}
      
timer_data_type platform_s_timer_op(unsigned id, int op, timer_data_type data)
{
  (void)id;
  (void)data;
  u32 res = 0;

  switch (op) {
  case PLATFORM_TIMER_OP_START:
    timer0_set(0xFFFFFFFF);
    res = 0xFFFFFFFF;
    break;
    
  case PLATFORM_TIMER_OP_READ:
    res = timer0_read();
    break;
    
  case PLATFORM_TIMER_OP_SET_CLOCK:
    /* Not supported. */
    res = 1000;
    break;
    
  case PLATFORM_TIMER_OP_GET_CLOCK:
    res = 1000;
    break;

  case PLATFORM_TIMER_OP_GET_MAX_DELAY:
    res = 0xFFFFFFFF;
    break;

  case PLATFORM_TIMER_OP_GET_MIN_DELAY:
    res = 1000;
    break;

  case PLATFORM_TIMER_OP_GET_MAX_CNT:
    res = 0xFFFFFFFF;
    break;
  }

  return res;
}

int platform_cpu_set_global_interrupts(int status)
{
  int prev;

  prev = platform_cpu_get_global_interrupts();

  if (status == PLATFORM_CPU_ENABLE) {
    asm("setpsw i");
  } else if (status == PLATFORM_CPU_DISABLE) {
    asm("clrpsw i");
  }

  return prev;
}

int platform_cpu_get_global_interrupts(void)
{
  unsigned long psw;

  asm("mvfc psw, %0"
      : "=r" (psw)
      : /* no input */
      : /* no clobbered */
  );

  return ((psw >> 16) & 0x1);
}


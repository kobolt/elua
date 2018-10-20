#include <iodefine.h>
#include "pio.h"

void pio_setup(void)
{
  /* Set all LED pins to output mode. */
  PORTA.PDR.BIT.B0 = 1;
  PORTA.PDR.BIT.B1 = 1;
  PORTA.PDR.BIT.B2 = 1;
  PORTA.PDR.BIT.B6 = 1;

  /* Set button pin to input mode. */
  PORTA.PDR.BIT.B7 = 0;
}

void pio_pin_set(int port, unsigned char pinmask)
{
  switch (port) {
  case 0:
    PORTA.PODR.BYTE = PORTA.PODR.BYTE | pinmask;
    break;
  default:
    break;
  }
}

void pio_pin_clear(int port, unsigned char pinmask)
{
  switch (port) {
  case 0:
    PORTA.PODR.BYTE = PORTA.PODR.BYTE & ~pinmask;
    break;
  default:
    break;
  }
}

unsigned char pio_pin_get(int port)
{
  switch (port) {
  case 0:
    return PORTA.PIDR.BYTE;
  default:
    return 0;
  }
}


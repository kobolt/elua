// RX63N CPU definition

#ifndef __CPU_RX63N_H__
#define __CPU_RX63N_H__

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// Number of resources (0 if not available/not implemented)
#define NUM_PIO               1
#define NUM_SPI               0
#define NUM_UART              1
#define NUM_TIMER             1
#define NUM_PWM               0
#define NUM_ADC               0
#define NUM_CAN               0

// CPU frequency (needed by the CPU module and MMCFS code, 0 if not used)
#define CPU_FREQUENCY         0

// PIO prefix ('0' for P0, P1, ... or 'A' for PA, PB, ...)
#define PIO_PREFIX            'A'
// Pins per port configuration:
#define PIO_PINS_PER_PORT 8

// Stack size definitions
#define STACK_SIZE_SVC   8192
#define STACK_SIZE_IRQ   32
#define STACK_SIZE_TOTAL ( STACK_SIZE_SVC + STACK_SIZE_IRQ )

// Allocator data: define your free memory zones here in two arrays
// (start address and end address)
#define SRAM_ORIGIN           0x00000000
#define SRAM_SIZE             0x40000
#define INTERNAL_RAM1_FIRST_FREE end
#define INTERNAL_RAM1_LAST_FREE  ( SRAM_ORIGIN + SRAM_SIZE - STACK_SIZE_TOTAL - 1 )

#endif // #ifndef __CPU_RX63N_H__


#ifndef DEFINE_H
#define DEFINE_H

/*

  Define stuff needed by multiple .h here to avoid redef
  #defines, y typedefs

*/
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define reserved_bits(x,y,z) uint8_t reserved##x[ z - y + 1 ]; 

typedef struct {
  uint32_t ticks;
  uint32_t* sp_irq;
} task_t;

#endif
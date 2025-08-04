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
  uint32_t r0a12[13];
  void (*pc)(void);      //LR_irq
  void (*lr)(void);      //LR_sys
  uint32_t sp;      //SP_sys
  uint32_t spsr;    
} context;

#endif
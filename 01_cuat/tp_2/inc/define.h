#ifndef DEFINE_H
#define DEFINE_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define reserved_bits(x,y,z) uint8_t reserved##x[ z - y + 1 ]; 



#endif
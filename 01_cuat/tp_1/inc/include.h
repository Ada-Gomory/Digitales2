#ifndef INCLUDE_H
#define INCLUDE_H

#include "low_level_cpu_access.h"
#include "gic.h"
#include "timer.h"
#include "uart.h"
#include "console_utils.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define reserved_bits(x,y,z) uint8_t reserved##x[z - y + 1];  //FIXME: repeated definition throws warn

#endif
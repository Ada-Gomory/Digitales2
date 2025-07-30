
#include "../../inc/include.h"

void __gic_init(void );

__attribute__((section(".kernel_text"))) void __gic_init() {

  _gicc_t* const GICC0 = (_gicc_t*)GICC0_ADDR;
  _gicd_t* const GICD0 = (_gicd_t*)GICD0_ADDR;

  GICC0->CTLR = 0x00000001;          // Habilita el GIC0     
  GICC0->PMR  = 0x000000F0;          // No maskea interrupciones

  GICD0->CTLR         = 0x00000001;  // Habilita las interrupciones
  GICD0->ISENABLER[1] |= 0x00000010; // Habilita interrupcion 36 (Timer 0-1)
  GICD0->ISENABLER[1] |= 0x00001000; // Habilita interrupcion 44 (UART 0)

    }

#include "../../inc/include.h"

__attribute__((section(".kernel_text"))) void task_fibonacci (void ){
    uint32_t a;
    uint32_t b;
  while (1) {
    a = 1;
    b = 1;
    printf_usr("Fibonacci: %d\n", a);
    printf_usr("Fibonacci: %d\n", b);

    while (a < 1000000){
      a += b;
      printf_usr("Fibonacci: %d\n", a);
      b += a;
      printf_usr("Fibonacci: %d\n", b);
    }
  }
}

__attribute__((section(".kernel_text"))) void task_collatz (void ){
  int a = 100000000;
  
  while (a != 1){
    if (a && 0b1){
      a = 3 * a;
      //print a
    } else
      a = a >> 1;
    //print a
  }
}

__attribute__((section(".kernel_text"))) void task_prime (void ){
  int a = 5646154;
  int b = 0;
  int once = 0;
  int fac = 2;
  
  while (a != 1){
    b = div(a, fac);
    if ((b*fac) == a){ //FIXME
      a = b;
      //print a
    } else {
      fac++;
      fac += once;
      once = 1;
    }
  }
} 
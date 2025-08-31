
#include "../../inc/include.h"

__attribute__((section(".kernel_text"))) void task_fibonacci (void ){
    uint32_t a;
    uint32_t b;
  while (1) {
    a = 1;
    b = 1;
    printf_usr("Fibonacci: %d\n", a);
    printf_usr("Fibonacci: %d\n", b);

    while (a < 100000000){
      a += b;
      printf_usr("Fibonacci: %d\n", a);
      b += a;
      printf_usr("Fibonacci: %d\n", b);
    }
  }
}

__attribute__((section(".kernel_text"))) void task_collatz (void ){
    uint32_t a;
    while (1){
    a = 100000000;
    printf_usr("\t\t\t\tCollatz: %d\n", a);

    while (a != 1){
      if (a & 0b1){
        a = 3*a;
        a += 1;
        a = a >> 1;
      } else
        a = a >> 1;
      printf_usr("\t\t\t\tCollatz: %d\n", a);
    }
  //while(1);
  }
}

__attribute__((section(".kernel_text"))) void task_prime (void ){
    uint32_t a;
    uint32_t b;
    uint32_t fac;
  while(1){
    a = 5646154;
    fac = 3;
    
    while(1) {
      if (!(a & 0b1)) a = a >> 1;        //if even divide by 2
      else break;                        //else continue
      printf_usr("\t\t\t\t\t\t\t\tPrime Factor: %d\n",2);
    }
    while (a != 1){
      b = div(a, fac);
      if ((b*fac) == a) {
        a = b;     //if is divisible by fac divide a by fac
        printf_usr("\t\t\t\t\t\t\t\tPrime Factor: %d\n",fac);
      }
      else fac += 2;              //increase factor; tests all odd divisiors but it's slower rather than strictly wrong; all negative
    }//*/

  }
}//*/
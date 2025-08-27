
#include "../../inc/include.h"

int int_global1 = 0;
int int_global2 = 0;

__attribute__((section(".kernel_text"))) void task_fibonacci (void ){
  while (1) {
    int a = 1;
    int b = 2;

    while (a < 1000000){
      a += b;
      // print a
      b += a;
      //print b
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
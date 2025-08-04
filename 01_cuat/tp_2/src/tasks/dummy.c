
#include "../../inc/include.h"

int int_global1 = 0;
int int_global2 = 0;

void tarea1 (void ){
  int int_t1 = 0;
  while (1){
    int_t1++;
    int_global1++;
  }
}

void tarea2 (void ){
  int int_t2 = 0;
  while (1){
    int_t2--;
    int_global2--;
  }
}

void tarea3 (void ){
  while (1){
    sizeof(int);
    int_global1--;
    int_global2--;
  }
}

void tarea_fibonacci (void ){
  int a = 1;
  int b = 2;

  while (a < 1000000){
    a += b;
    // print a
    b += a;
    //print b
  }
}

void tarea_collatz (void ){
  int a = 100000000;
  
  while (a != 1){
    if (a && 0b1){
      a = a >> 1;
      //print a
    } else
    a = 3 * a;
    //print a
  }
}

void tarea_prime (void ){
  int a = 5646154;
  int b = 0;
  int once = 0;
  int fac = 2;
  
  while (a != 1){
    b = div(a, fac);
    if ((b*fac) == a){
      a = b;
      //print a
    }
    b++;
    b += once;
    once = 1;
  }
}
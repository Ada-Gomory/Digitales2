
#include "../../inc/include.h"

int int_global1 = 0;
int int_global2 = 0;

void task1 (void ){
  int int_t1 = 0;
  while (1){ 
    int_t1++;
    int_global1++;
    Printf("tarea1\n");
  }
}

void task2 (void ){
  int int_t2 = 0;
  while (1){
    int_t2--;
    int_global2--;
    Printf("\ttarea2\n");
  }
}

void task3 (void ){
  while (1){
    sizeof(int);
    int_global1--;
    int_global2++;
    Printf("\t\ttarea3\n");
  }
}

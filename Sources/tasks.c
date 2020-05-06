#include "os.h"

void task1(void) {
  int i = 0;
  for(;;){
    i++;
    #if with_scheduler == 1
    delay(10);
    #else
    yield();
    #endif
  }
}

void task2(void) {
  int i = 0;
  for(;;){
    i++;
    #if with_scheduler == 1
    delay(20);
    #else
    yield();
    #endif
  }
}

void task3(void) {
  int i = 0;
  for(;;){
    i++;
    #if with_scheduler == 1
    delay(30);
    #else
    yield();
    #endif
  }
}


void task4(void) {
  int i = 0;
  for(;;){
    i++;
      #if with_scheduler == 1
        delay(30);
      #else
        yield();
      #endif
  }
}

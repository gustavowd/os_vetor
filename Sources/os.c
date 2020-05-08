#include "os.h"
#include <stdlib.h>

volatile TCB_t TCB[4];
cpu_t idle_stk[128];

volatile cpu_t ct = 0;
volatile cpu_t it = 0;
volatile long long os_time = 0;


void idle(void) {
  for(;;){
    // dorme aqui
  }
}


cpu_t *scheduler(void){
  cpu_t i = 0;
  cpu_t higher_prio = 0;
  cpu_t higher_task = 0;
  
  for(i=0;i<it;i++){
    if(TCB[i].ready == 1){
      if (TCB[i].prio >= higher_prio){
        higher_prio = TCB[i].prio;
        higher_task = i;
      }
    }
  }
  ct = higher_task;
  return TCB[higher_task].stk;
}



void start_os(void){
  InstallTask(idle, 0, idle_stk, sizeof(idle_stk));
  init_os_timer();
  
  stk_tmp = scheduler();
  
  dispatcher();
}


void delay(long long timeout){
  TCB[ct].timeout = timeout + os_time;
  TCB[ct].ready = 0;
  yield();
}


cpu_t os_inc_and_compare(void){
  int i;
  cpu_t ready = 0;
  os_time++;
  
  for(i=0;i<it;i++){
    if(TCB[i].timeout == os_time){
      TCB[i].ready = 1;
      ready = 1;
    }
  }
  
  return ready;
}


void InstallTask(task_t task, cpu_t prio, cpu_t *stk, int stk_size){
  TCB[it].stk = PrepareStack(task, stk, stk_size);
  TCB[it].prio = prio;
  TCB[it].ready = 1;
  it++;
}

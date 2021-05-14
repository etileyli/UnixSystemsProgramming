  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <pthread.h>
  #include <semaphore.h>
  #include "ds.h"

  void scheduler(void *anyParam);
  void TaskA(void *);
  void TaskB(void *);
  void TaskC(void *);
  void TaskD(void *);

  queue *queFCFS;

  int main(int argc, char const *argv[]) {

    queFCFS = createQueue();

    int pid_A, pid_B, pid_C, pid_D;

    void *par = NULL;

    int t = 0;
    while(t<8){

      switch(t){
        case 2:
          enqueue_proc2(makeProc2(&pid_A, 3, TaskA, "TaskA"), queFCFS);
          break;
        case 3:
          enqueue_proc2(makeProc2(&pid_B, 2, TaskB, "TaskB"), queFCFS);
          break;
        case 6:
          enqueue_proc2(makeProc2(&pid_C, 1, TaskC, "TaskC"), queFCFS);
          break;
        case 7:
          enqueue_proc2(makeProc2(&pid_D, 4, TaskD, "TaskD"), queFCFS);
          break;
      }
      t++;
      scheduler(par);
      sleep(1);
    }

    return 0;
  }

void scheduler(void *param){


  pcbptr *thrdNode = dequeue_proc(queFCFS);

  if (thrdNode == NULL){
    printf("No thread in queue.\n");
    return;
  }
  //
  printf("Now task: %s\n", thrdNode->thread.name);
  sem_post(&thrdNode->thread.sem);
}

void TaskA(void *param){

  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskA: CPU\n");
  sem_post(&(((pcbptr *)param)->thread.sem));
}

void TaskB(void *param){

    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskB is running.\n");
    sem_post(&(((pcbptr *)param)->thread.sem));
}

void TaskC(void *param){
    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskC: is the best\n");
    sem_post(&(((pcbptr *)param)->thread.sem));
}

void TaskD(void *param){
  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskD: is the last\n");
  sem_post(&(((pcbptr *)param)->thread.sem));
}

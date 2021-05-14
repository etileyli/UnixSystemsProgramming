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

  sem_t semA, semB, semC, semD;

  int main(int argc, char const *argv[]) {

    queFCFS = createQueue();

    pcbptr *thrdNode = NULL;

    // queue *quePB = createQueue();

    int pid_A, pid_B, pid_C, pid_D;

    // void *par = NULL;

    // displayQueue(queFCFS);

    // pcbptr *temp = dequeue_proc(queFCFS);
    // displayNode(temp);
    // int taskID = temp->thread.taskID;
    // (*fun_ptr_arr[taskID])(par);
    // temp->ftpr(par);

    void *par = NULL;

    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    sem_init(&semD, 0, 0);

    enqueue_proc2(makeProc2(&pid_A, 3, TaskA), queFCFS);
    enqueue_proc2(makeProc2(&pid_B, 2, TaskB), queFCFS);
    enqueue_proc2(makeProc2(&pid_C, 1, TaskC), queFCFS);
    enqueue_proc2(makeProc2(&pid_D, 4, TaskD), queFCFS);

    // pthread_t threadTemp0;
    // pthread_create( &threadTemp0, NULL, (void *)scheduler, (void *) NULL);
    // pthread_join(threadTemp0, NULL);

    int t = 0;
    while(1){
      // 
      // switch(t){
      //   case 2:
      //     enqueue_proc2(makeProc2(&pid_A, 3, TaskA), queFCFS);
      //     break;
      //   case 3:
      //     enqueue_proc2(makeProc2(&pid_B, 2, TaskB), queFCFS);
      //     break;
      //   case 6:
      //     enqueue_proc2(makeProc2(&pid_C, 1, TaskC), queFCFS);
      //     break;
      //   case 7:
      //     enqueue_proc2(makeProc2(&pid_D, 4, TaskD), queFCFS);
      //     break;
      // }
      // t++;
      //
      scheduler(par);
      sleep(1);
    }

    return 0;
  }

void scheduler(void *param){

  static int t = 0;
  int pid_A, pid_B, pid_C, pid_D;

  switch(t){
    case 1:
      printf("Now task A:\n");
      sem_post(&semA);
      sleep(1);
      break;
    case 2:
      printf("Now task C:\n");
      sem_post(&semC);
      sleep(1);
      break;
    case 3:
      printf("Now task D:\n");
      sem_post(&semD);
      sleep(1);
      break;
    case 4:
      printf("Now task B:\n");
      sem_post(&semB);
      sleep(1);
      break;
    case 5:
      enqueue_proc2(makeProc2(&pid_B, 2, TaskB), queFCFS);
      printf("Now task B:\n");
      sem_post(&semB);
      sleep(1);
      break;
    case 6:
      enqueue_proc2(makeProc2(&pid_D, 2, TaskD), queFCFS);
      printf("Now task D:\n");
      sem_post(&semD);
      sleep(1);
      break;
    case 7:
      enqueue_proc2(makeProc2(&pid_C, 2, TaskC), queFCFS);
      printf("Now task C:\n");
      sem_post(&semC);
      sleep(1);
      break;
    case 8:
      enqueue_proc2(makeProc2(&pid_A, 2, TaskA), queFCFS);
      printf("Now task A:\n");
      sem_post(&semA);
      sleep(1);
      break;
  }
  t++;
}

void TaskA(void *param){
  sem_wait(&semA);
  // sleep(1);
  printf("TaskA: CPU\n");
  sem_post(&semA);
}

void TaskB(void *param){
  sem_wait(&semB);
  // sleep(1);
  printf("TaskB\n");
  sem_post(&semB);
}

void TaskC(void *param){
  sem_wait(&semC);
  // sleep(1);
  printf("TaskC\n");
  sem_post(&semC);
}

void TaskD(void *param){
  sem_wait(&semD);
  // sleep(1);
  printf("TaskD\n");
  sem_post(&semD);
}

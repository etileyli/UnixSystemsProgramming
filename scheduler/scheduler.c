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

  sem_t semScheduler;

  int main(int argc, char const *argv[]) {

    queFCFS = createQueue();

    sem_init(&semScheduler , 0, 1);

    int pid_A, pid_B, pid_C, pid_D;

    void *par = NULL;

    int t = 0;

    pthread_t threadTemp;
    pthread_create(&threadTemp, NULL, (void *)scheduler, (void *)NULL);

    while(t<9){

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
      sleep(1);
    }
    pthread_join(threadTemp, NULL);
    return 0;
  }

void scheduler(void *param){

  while(1){
    sem_wait(&semScheduler);
    pcbptr *thrdNode = dequeue_proc(queFCFS);

    if (thrdNode == NULL){
      // printf("No thread in queue.\n");
      sem_post(&semScheduler);
      continue;
    }

    printf("Now task: %s\n", thrdNode->thread.name);
    sem_post(&thrdNode->thread.sem);
  }
}

void TaskA(void *param){

  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskA: CPU\n");
  sleep(3);
  printf("TaskA: CPU is finished.\n");
  sem_post(&semScheduler);
}

void TaskB(void *param){

    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskB is running.\n");
    sleep(5);
    printf("TaskB is finished.\n");
    sem_post(&semScheduler);
}

void TaskC(void *param){
    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskC: is the best\n");
    sleep(2);
    printf("TaskC: is finished.\n");
    sem_post(&semScheduler);
}

void TaskD(void *param){
  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskD: is the last\n");
  sleep(1);
  printf("TaskD: is finished.\n");
  sem_post(&semScheduler);
}

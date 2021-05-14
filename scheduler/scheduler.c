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

    enqueue_proc2(makeProc2(&pid_A, 3, TaskA), queFCFS);
    enqueue_proc2(makeProc2(&pid_B, 2, TaskB), queFCFS);
    enqueue_proc2(makeProc2(&pid_C, 1, TaskC), queFCFS);
    enqueue_proc2(makeProc2(&pid_D, 4, TaskD), queFCFS);
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

    // while(1){
      // scheduler(par);
      // (*fun_ptr_arr[i%3])(par);

      pthread_t threadTemp0;
      pthread_create( &threadTemp0, NULL, (void *)scheduler, (void *) NULL);

      pthread_t threadTemp1;
      pthread_create( &threadTemp1, NULL, (void *)TaskA, (void *) NULL);
      pthread_t threadTemp2;
      pthread_create( &threadTemp2, NULL, (void *)TaskB, (void *) NULL);
      pthread_t threadTemp3;
      pthread_create( &threadTemp3, NULL, (void *)TaskC, (void *) NULL);
      pthread_t threadTemp4;
      pthread_create( &threadTemp4, NULL, (void *)TaskD, (void *) NULL);
      pthread_join(threadTemp0, NULL);
      pthread_join(threadTemp1, NULL);
      pthread_join(threadTemp2, NULL);
      pthread_join(threadTemp3, NULL);
      pthread_join(threadTemp4, NULL);
      /* Simulate arrival of the threads. */
      // switch(t){
      //   case 0:
      //     enqueue_proc2(makeProc2(&thread1, 0), queFCFS);
      //     break;
      //   case 2:
      //     enqueue_proc2(makeProc2(&thread2, 0), queFCFS);
      //     break;
      //   case 3:
      //     enqueue_proc2(makeProc2(&thread3, 0), queFCFS);
      //     break;
      //   case 7:
      //     enqueue_proc2(makeProc2(&thread4, 0), queFCFS);
      //     break;
      // }
      // sleep(1);
      /* END OF Simulate arrival of the threads. */

      // pcbptr *temp = dequeue_proc(queFCFS);
      // displayNode(temp);
      // temp->ftpr(par);
      // int taskID = temp->thread.taskID;
      // (*fun_ptr_arr[taskID])(par);

      // printf("****************** t = %d\n",t++);
      // displayQueue(queFCFS);

    // }

    return 0;
  }

void scheduler(void *param){
  // printf("scheduler\n");
  // sleep(1);
  // pcbptr *temp = dequeue_proc(queFCFS);
  // temp->ftpr(param);
  sleep(2);

  printf("Now task A:\n");
  sem_post(&semA);
  sleep(2);

  printf("Now task C:\n");
  sem_post(&semC);
  sleep(2);

  printf("Now task D:\n");
  sem_post(&semD);
  sleep(2);

  printf("Now task B:\n");
  sem_post(&semB);
  sleep(2);

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

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
  void TaskE(void *);
  void TaskF(void *);
  void TaskG(void *);
  void TaskH(void *);

  queue *queFCFS;
  queue *quePB;

  sem_t semScheduler;

  pthread_mutex_t lock;

  int main(int argc, char const *argv[]) {

    queFCFS = createQueue();
    quePB = createQueue();

    sem_init(&semScheduler , 0, 1);
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    int pid_A, pid_B, pid_C, pid_D;
    int pid_E, pid_F, pid_G, pid_H;

    void *par = NULL;

    int t = 0;

    /* Task arrival simulation loop. */
    while(1){
      pthread_t threadTemp;
      pthread_create(&threadTemp, NULL, (void *)scheduler, (void *)NULL);

      switch(t){
        case 1:
          pthread_mutex_lock(&lock);
          enqueue_proc2(makeProc2(&pid_A, 1, TaskA, "TaskA"), queFCFS);
          pthread_mutex_unlock(&lock);
          break;
        case 2:
          pthread_mutex_lock(&lock);
          enqueue_proc2(makeProc2(&pid_B, 1, TaskB, "TaskB"), queFCFS);
          pthread_mutex_unlock(&lock);
          break;
        case 3:
          pthread_mutex_lock(&lock);
          enqueue_proc2(makeProc2(&pid_C, 1, TaskC, "TaskC"), queFCFS);
          pthread_mutex_unlock(&lock);
          break;
        case 4:
          pthread_mutex_lock(&lock);
          enqueue_proc2(makeProc2(&pid_D, 1, TaskD, "TaskD"), queFCFS);
          pthread_mutex_unlock(&lock);
          break;
        case 5:
          pthread_mutex_lock(&lock);
          insert_proc2(makeProc2(&pid_E, 3, TaskE, "TaskE"), quePB);
          pthread_mutex_unlock(&lock);
          break;
        case 6:
          pthread_mutex_lock(&lock);
          insert_proc2(makeProc2(&pid_F, 4, TaskF, "TaskF"), quePB);
          pthread_mutex_unlock(&lock);
          break;
        case 7:
          pthread_mutex_lock(&lock);
          insert_proc2(makeProc2(&pid_G, 3, TaskG, "TaskG"), quePB);
          pthread_mutex_unlock(&lock);
          break;
        case 8:
          pthread_mutex_lock(&lock);
          insert_proc2(makeProc2(&pid_H, 0, TaskH, "TaskH"), quePB);
          pthread_mutex_unlock(&lock);
          break;
      }
      t++;
      usleep(1000000);
    }
    // pthread_join(threadTemp, NULL);

    return 0;
  }

void scheduler(void *param){

  // while(1){

    sem_wait(&semScheduler);
    pthread_mutex_lock(&lock);

    /*If the queue is not empty */
    pcbptr *thrdNode, *thrdNodeFCFS, *thrdNodePB;

    thrdNodeFCFS = copyFront(queFCFS);
    thrdNodePB = copyFront(quePB);

    /* Both queues are empty. Continue until a task arrives to either queue. */
    if ((thrdNodeFCFS == NULL) && (thrdNodePB == NULL)){
        pthread_mutex_unlock(&lock);
        sem_post(&semScheduler);
        return;
    }
    /* Both queues are not empty. Decide the task to run.*/
    else if ((thrdNodeFCFS != NULL) && (thrdNodePB != NULL)){
      if(thrdNodePB->thread.priority >= thrdNodeFCFS->thread.priority){
        thrdNode = dequeue_proc(quePB);
      }
      else{
        thrdNode = dequeue_proc(queFCFS);
      }
    }
    else if (thrdNodePB != NULL){
      thrdNode = dequeue_proc(quePB);
    }
    else if (thrdNodeFCFS != NULL){
      thrdNode = dequeue_proc(queFCFS);
    }

    printf("Now task: %s\n", thrdNode->thread.name);

    pthread_mutex_unlock(&lock);
    sem_post(&thrdNode->thread.sem);
  // }
}

void TaskA(void *param){

  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskA: CPU\n");
  sleep(4);
  printf("TaskA: CPU is finished.\n");
  sem_post(&semScheduler);
}

void TaskB(void *param){

    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskB is running.\n");
    sleep(8);
    printf("TaskB is finished.\n");
    sem_post(&semScheduler);
}

void TaskC(void *param){
    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskC: is the best\n");
    sleep(3);
    printf("TaskC: is finished.\n");
    sem_post(&semScheduler);
}

void TaskD(void *param){
  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskD: is the last\n");
  sleep(4);
  printf("TaskD: is finished.\n");
  sem_post(&semScheduler);
}

void TaskE(void *param){

  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskE: CPU\n");
  sleep(3);
  printf("TaskE: CPU is finished.\n");
  sem_post(&semScheduler);
}

void TaskF(void *param){

  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskF: CPU\n");
  for (int i = 0; i < 1000000000; i++){
  }
  printf("TaskF: CPU is finished.\n");
  sem_post(&semScheduler);
}

void TaskG(void *param){
    sem_wait(&(((pcbptr *)param)->thread.sem));
    printf("TaskG: is the best\n");
    sleep(2);
    printf("TaskG: is finished.\n");
    sem_post(&semScheduler);
}

void TaskH(void *param){
  sem_wait(&(((pcbptr *)param)->thread.sem));
  printf("TaskH: is the last\n");
  sleep(1);
  printf("TaskH: is finished.\n");
  sem_post(&semScheduler);
}

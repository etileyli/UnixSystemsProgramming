  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include "ds.h"

  void *scheduler(void *anyParam);
  void TaskA(void *);
  void TaskB(void *);
  void TaskC(void *);

  int main(int argc, char const *argv[]) {

    queue *queFCFS = createQueue();

    // queue *quePB = createQueue();

    int thread1, thread2, thread3, thread4, thread5, thread6, thread7;

    void (*fun_ptr_arr[3])(void *) = {TaskA, TaskB, TaskC};

    void *par = NULL;
    int i = 0;
    while(1){
      (*fun_ptr_arr[i%3])(par);
      sleep(1);
      i++;
    }

    return 0;
  }

void TaskA(void *param){
  printf("TaskA\n");
}

void TaskB(void *param){
  printf("TaskB\n");
}

void TaskC(void *param){
  printf("TaskC\n");
}

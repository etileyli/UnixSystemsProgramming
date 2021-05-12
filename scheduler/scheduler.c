  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include "ds.h"

  void *scheduler(void *anyParam);
  void TaskA(void *);
  void TaskB(void *);
  void TaskC(void *);
  void TaskD(void *);

  int main(int argc, char const *argv[]) {

    queue *queFCFS = createQueue();

    pcbptr *thrdNode = NULL;

    // queue *quePB = createQueue();

    int pid_A, pid_B, pid_C, pid_D;

    void (*fun_ptr_arr[5])(void *) = {TaskA, TaskB, TaskC, TaskD};

    void *par = NULL;
    int t = 4;

    enqueue_proc2(makeProc2(&pid_A, 0, TaskA), queFCFS);
    enqueue_proc2(makeProc2(&pid_B, 0, TaskB), queFCFS);
    enqueue_proc2(makeProc2(&pid_C, 0, TaskC), queFCFS);
    enqueue_proc2(makeProc2(&pid_D, 0, TaskD), queFCFS);
    // displayQueue(queFCFS);

    // pcbptr *temp = dequeue_proc(queFCFS);
    // displayNode(temp);
    // int taskID = temp->thread.taskID;
    // (*fun_ptr_arr[taskID])(par);
    // temp->ftpr(par);

    while(t){
      // (*fun_ptr_arr[i%3])(par);

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

      pcbptr *temp = dequeue_proc(queFCFS);
      // displayNode(temp);
      temp->ftpr(par);
      // int taskID = temp->thread.taskID;
      // (*fun_ptr_arr[taskID])(par);

      // printf("****************** t = %d\n",t++);
      // displayQueue(queFCFS);
      t--;
    }



    return 0;
  }

// void scheduler(void *param){
//   printf("scheduler\n");
//   sleep(1);
// }

void TaskA(void *param){
  printf("TaskA\n");
  sleep(4);
}

void TaskB(void *param){
  printf("TaskB\n");
  sleep(8);
}

void TaskC(void *param){
  printf("TaskC\n");
  sleep(2);
}

void TaskD(void *param){
  printf("TaskD\n");
  sleep(1);
}

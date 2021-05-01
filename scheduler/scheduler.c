#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  queue *que1 = (queue *)malloc(sizeof(struct queue));
  pcbptr *thrdNode = NULL;

  for (int i = 0; i < 4; i++){
    enqueue_proc(thrdNode = createThread(), que1);
    displayNode(thrdNode);
  }

  printf("Threads are created!\n\n");

  // displayFront(que1);
  // displayRear(que1);

  // pcbptr *thrdNode = dequeue_proc(que1);

  // displayFront(que1);
  // displayRear(que1);

  // displayNode(thrdNode);

  // displayPCBTable();
  // displayQueue(que1);
  // pcbptr *thrdNode = dequeue_proc(que1);
  // displayQueue(que1);
  //
  // displayNode(thrdNode);
  // printf("****\n");
  // displayPCBTable();

  delete_proc(getPCBFromTable(1), que1);
  // displayQueue(que1);
  printf("\n1st proc is deleted. The Queue is:\n");
  displayQueue(que1);

  delete_proc(getPCBFromTable(2), que1);
  // displayQueue(que1);

  delete_proc(getPCBFromTable(3), que1);
  // displayQueue(que1);

  delete_proc(getPCBFromTable(4), que1);
  printf("\nAll processes are deleted.\n");
  displayQueue(que1);


  enqueue_proc(thrdNode = createThread(), que1);
  enqueue_proc(thrdNode = createThread(), que1);
  printf("\nThreads 5 and 6 is added to the que.\n\n");

  printf("Front of the queue is: \n");
  displayFront(que1);
  printf("\nThe queue is :\n");
  displayQueue(que1);

  delete_proc(getPCBFromTable(2), que1);
  printf("Non-existent process 2 is deleted. Queue is\n");
  displayQueue(que1);

  delete_proc(getPCBFromTable(5), que1);
  printf("\nProcess 5 is deleted. Queue is:\n");
  displayQueue(que1);

  delete_proc(getPCBFromTable(6), que1);
  printf("\nProcess 6 is deleted. Queue is:\n");
  displayQueue(que1);

  return 0;
}

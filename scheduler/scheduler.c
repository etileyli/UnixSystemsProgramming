#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  queue *queFCFS = (queue *)malloc(sizeof(struct queue));
  queue *quePB = (queue *)malloc(sizeof(struct queue));
  pcbptr *thrdNode = NULL;

  // for (int i = 0; i < 4; i++){
  //   enqueue_proc(thrdNode = makeProc(0), queFCFS);
  //   displayNode(thrdNode);
  // }
  //
  // printf("Threads are created!\n\n");

  // displayFront(queFCFS);
  // displayRear(queFCFS);

  // pcbptr *thrdNode = dequeue_proc(queFCFS);

  // displayFront(queFCFS);
  // displayRear(queFCFS);

  // displayNode(thrdNode);

  // displayPCBTable();
  // displayQueue(queFCFS);
  // pcbptr *thrdNode = dequeue_proc(queFCFS);
  // displayQueue(queFCFS);
  //
  // displayNode(thrdNode);
  // printf("****\n");
  // displayPCBTable();

  // delete_proc(getPCBFromTable(1), queFCFS);
  // // displayQueue(queFCFS);
  // printf("\n1st proc is deleted. The Queue is:\n");
  // displayQueue(queFCFS);
  //
  // delete_proc(getPCBFromTable(2), queFCFS);
  // // displayQueue(queFCFS);
  //
  // delete_proc(getPCBFromTable(3), queFCFS);
  // // displayQueue(queFCFS);
  //
  // delete_proc(getPCBFromTable(4), queFCFS);
  // printf("\nAll processes are deleted.\n");
  // displayQueue(queFCFS);
  //
  //
  // enqueue_proc(thrdNode = makeProc(0), queFCFS);
  // enqueue_proc(thrdNode = makeProc(0), queFCFS);
  // printf("\nThreads 5 and 6 is added to the que.\n\n");
  //
  // printf("Front of the queue is: \n");
  // displayFront(queFCFS);
  // printf("\nThe queue is :\n");
  // displayQueue(queFCFS);
  //
  // delete_proc(getPCBFromTable(2), queFCFS);
  // printf("Non-existent process 2 is deleted. Queue is\n");
  // displayQueue(queFCFS);
  //
  // delete_proc(getPCBFromTable(5), queFCFS);
  // printf("\nProcess 5 is deleted. Queue is:\n");
  // displayQueue(queFCFS);
  //
  // delete_proc(getPCBFromTable(6), queFCFS);
  // printf("\nProcess 6 is deleted. Queue is:\n");
  // displayQueue(queFCFS);
  //
  // printf("\nPCB Table:\n");
  // displayPCBTable();

  for (int i = 0; i < 4; i++){
    insert_proc(thrdNode = makeProc(i), quePB);
    displayNode(thrdNode);
  }

  printf("Threads are created!\n\n");

  printf("The Queue:\n");
  displayQueue(quePB);
  // insert_proc(thrdNode = makeProc(2), quePB);
  // insert_proc(thrdNode = makeProc(4), quePB);
  // printf("\nThreads 5 and 6 is added to the que.\n\n");
  // displayQueue(quePB);

  return 0;
}

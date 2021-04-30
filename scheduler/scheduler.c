#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  queue *que1 = (queue *)malloc(sizeof(struct queue));

  for (int i = 0; i < 4; i++){
    pcbptr *thrdNode = NULL;
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

  delete_proc(getPCBFromTable(2), que1);
  displayQueue(que1);

  delete_proc(getPCBFromTable(3), que1);
  displayQueue(que1);

  return 0;
}

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

  displayFront(que1);
  displayRear(que1);

  pcbptr *thrdNode = dequeue_proc(que1);

  displayFront(que1);
  displayRear(que1);

  displayNode(thrdNode);
  return 0;
}

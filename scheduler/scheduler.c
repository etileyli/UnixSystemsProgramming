#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  for (int i = 0; i < 4; i++){
    pcbptr *thrdNode = NULL;
    enqueue_proc(thrdNode = createThread());
    displayNode(thrdNode);
  }

  displayFront();
  displayRear();

  pcbptr *thrdNode = dequeue_proc();

  displayFront();
  displayRear();

  displayNode(thrdNode);
  return 0;
}

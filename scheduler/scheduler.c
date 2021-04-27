#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  for (int i = 0; i < 4; i++){
    threadNode *thrdNode = NULL;
    insert(thrdNode = createThread());
    displayNode(thrdNode);
  }

  displayFront();
  displayRear();

  delete();


  displayFront();
  displayRear();

  return 0;
}

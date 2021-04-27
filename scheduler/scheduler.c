#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  for (int i = 0; i < 4; i++){
    threadNode *thrdNode = NULL;
    thrdNode = createThread();
    insert(thrdNode);
    displayNode(thrdNode);
  }

  return 0;
}

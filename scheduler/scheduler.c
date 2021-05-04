#include <stdio.h>
#include <stdlib.h>
#include "ds.h"


int main(int argc, char const *argv[]) {

  queue *queFCFS = createQueue();

  // queue *quePB = createQueue();

  int thread1, thread2, thread3, thread4, thread5, thread6, thread7;

  // displayNode2(thread1);

  // enqueue_proc2(makeProc2(&thread1, 1), queFCFS);
  // enqueue_proc2(makeProc2(&thread2, 2), queFCFS);
  // enqueue_proc2(makeProc2(&thread3, 3), queFCFS);
  // enqueue_proc2(makeProc2(&thread4, 4), queFCFS);

  insert_proc2(makeProc2(&thread1, 1), queFCFS);
  insert_proc2(makeProc2(&thread2, 2), queFCFS);
  insert_proc2(makeProc2(&thread3, 3), queFCFS);
  insert_proc2(makeProc2(&thread4, 4), queFCFS);

  // printf("The Queue:\n");
  // displayQueue(queFCFS);
  //
  // dequeue_proc(queFCFS);
  // dequeue_proc(queFCFS);
  //
  // printf("The Queue after deletion:\n");
  // displayQueue(queFCFS);

  // printf("The PCB Table:\n");
  // displayPCBTable();

  insert_proc2(makeProc2(&thread5, 0), queFCFS);
  insert_proc2(makeProc2(&thread6, 8), queFCFS);
  insert_proc2(makeProc2(&thread7, 3), queFCFS);

  printf("The Queue:\n");
  displayQueue(queFCFS);

  // delete_proc2(thread5, queFCFS);
  // delete_proc2(thread6, queFCFS);
  // delete_proc2(thread7, queFCFS);

  del_proc2(thread5, queFCFS);
  del_proc2(thread6, queFCFS);
  del_proc2(thread7, queFCFS);

  printf("The Queue after deletion:\n");
  displayQueue(queFCFS);

  printf("The PCB Table:\n");
  displayPCBTable();

  insert_proc2(makeProc2(&thread5, 1), queFCFS);
  insert_proc2(makeProc2(&thread6, 7), queFCFS);
  insert_proc2(makeProc2(&thread7, 2), queFCFS);

  printf("The Queue after re-insertation:\n");
  displayQueue(queFCFS);

  printf("The PCB Table:\n");
  displayPCBTable();


  return 0;
}

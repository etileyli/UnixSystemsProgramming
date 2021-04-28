#include <stdlib.h>
#include <stdio.h>

typedef struct pcb{
  int taskID;
  int priority;
  int type;
  int dataArea;
  int sem;
}pcb;

typedef struct pcbptr{
  pcb thread;
  struct pcbptr *next;
}pcbptr;



pcbptr *createThread();
void enqueue_proc();
pcbptr *dequeue_proc();
void displayNode();
void displayFront();
void displayRear();

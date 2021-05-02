#include <stdlib.h>
#include <stdio.h>

#define MAX_PROCESS_NUMBER 100

typedef struct pcb{
  int taskID;
  int priority;
  int type;
  int dataArea;
  int sem;
  int state;
}pcb;

typedef struct pcbptr{
  pcb thread;
  struct pcbptr *next;
}pcbptr;

typedef struct queue{
  pcbptr *front;
  pcbptr *rear;
  int state;
}queue;

queue *createQueue();
pcbptr *makeProc(int prioritry);
void enqueue_proc(pcbptr *thread, queue *que);
pcbptr *dequeue_proc(queue *que);
pcbptr *getPCBFromTable(int index);
void insert_proc(pcbptr *newThread, queue *que);
void delete_proc(pcbptr *deletedThread, queue *que);
pcbptr *del_proc(int index, queue *que);
int checkQueue(queue *que);
void displayNode(pcbptr *thrdNode);
void displayFront(queue *que);
void displayRear(queue *que);
void displayPCBTable();
void displayQueue(queue *que);

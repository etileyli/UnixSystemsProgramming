#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PROCESS_NUMBER 100

typedef struct pcb{
  int taskID;
  int priority;
  int type;
  int dataArea;
  sem_t sem;
  int state;
  char* name;
}pcb;

typedef struct pcbptr{
  void (*ftpr)(void *p);
  pcb thread;
  struct pcbptr *next;
}pcbptr;

typedef struct queue{
  pcbptr *front;
  pcbptr *rear;
  int state;
}queue;

queue *createQueue();
int makeProc2(int *threadAddress, int prioritry, void (*ftpr)(void *p), char *name);
int findSuitableIndex();
int enqueue_proc2(int pid, queue *que);
pcbptr *dequeue_proc(queue *que);
pcbptr *getPCBFromTable(int index);
int insert_proc2(int pid, queue *que);
int delete_proc2(int pid, queue *que);
pcbptr *del_proc2(int pid, queue *que);
int checkQueue(queue *que);
void displayNode(pcbptr *thrdNode);
void displayNode2(int pid);
void displayFront(queue *que);
pcbptr *copyFront(queue *que);
void displayRear(queue *que);
void displayPCBTable();
void displayQueue(queue *que);

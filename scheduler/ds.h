#include <stdlib.h>
#include <stdio.h>

typedef struct pcb{
  int taskID;
  int priority;
  int type;
  int dataArea;
  int sem;
}pcb;

typedef struct threadNode{
  pcb thread;
  struct threadNode *next;
}threadNode;



threadNode *createThread();
void insert();
void delete();
void displayNode();
void displayFront();
void displayRear();

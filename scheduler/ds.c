#include "ds.h"

static int taskID = 0;

void displayNode(pcbptr *thrdNode){

  printf("Thread No = %d \n", thrdNode->thread.taskID);
  printf("Thread priority = %d \n", thrdNode->thread.priority);
  printf("Thread dataArea = %d \n", thrdNode->thread.dataArea);
  printf("\n");
}

void displayRear(queue *que){
  printf("Rear:\n");
  displayNode(que->rear);
}

void displayFront(queue *que){
  printf("Front:\n");
  displayNode(que->front);
}

pcbptr *createThread(){

  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));

  if(thrdNode == NULL){
    perror("Unable to allocate thread node");
    exit(1);
  }

  thrdNode->thread.taskID = ++taskID;
  thrdNode->thread.priority = 0;
  thrdNode->thread.dataArea = 111;

  return thrdNode;
}

void enqueue_proc(pcbptr *thread, queue *que){

  if (que->front == NULL){
    que->front = thread;
    que->rear = thread;
    que->front->next = NULL;
    que->rear->next = NULL;
  }
  else{
    que->rear->next = thread;
    que->rear = thread;
    que->rear->next = NULL;
  }
}

pcbptr *dequeue_proc(queue *que)
{
  if(que->front == NULL)
  {
      printf("The queue is aready emtpy!\n");
      return NULL;
  }
  else
  {
      pcbptr *thread = que->front;
      que->front = que->front->next;
      return thread;
  }
}

#include "ds.h"

static pcbptr *front = NULL;
static pcbptr *rear = NULL;

static int taskID = 0;

void displayNode(pcbptr *thrdNode){

  printf("Thread No = %d \n", thrdNode->thread.taskID);
  printf("Thread priority = %d \n", thrdNode->thread.priority);
  printf("Thread dataArea = %d \n", thrdNode->thread.dataArea);
  printf("\n");
}

void displayRear(){
  printf("Rear:\n");
  displayNode(rear);
}

void displayFront(){
  printf("Front:\n");
  displayNode(front);
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

void enqueue_proc(pcbptr *thread){

  if (front == NULL){
    front = thread;
    rear = thread;
    front->next = NULL;
    rear->next = NULL;
  }
  else{
    rear->next = thread;
    rear = thread;
    rear->next = NULL;
  }
}

pcbptr *dequeue_proc()
{
  if(front == NULL)
  {
      printf("The queue is aready emtpy!\n");
      return NULL;
  }
  else
  {
      pcbptr *thread = front;
      front = front->next;
      return thread;
  }
}

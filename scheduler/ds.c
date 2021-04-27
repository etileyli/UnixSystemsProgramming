#include "ds.h"

static threadNode *front = NULL;
static threadNode *rear = NULL;

static int taskID = 0;

void displayNode(threadNode *thrdNode){

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


threadNode *createThread(){

  threadNode *thrdNode = (threadNode *)malloc(sizeof(struct threadNode));

  if(thrdNode == NULL){
    perror("Unable to allocate thread node");
    exit(1);
  }

  thrdNode->thread.taskID = ++taskID;
  thrdNode->thread.priority = 0;
  thrdNode->thread.dataArea = 111;

  return thrdNode;
}

void insert(threadNode *thread){

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

void delete ()
{
  if(front == NULL)
  {
      printf("The queue is aready emtpy!\n");
  }
  else
  {
      threadNode *thread = front;
      front = front->next;
      free(thread);
  }
}

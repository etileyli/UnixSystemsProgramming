#include "ds.h"

static pcbptr *pcbTable[MAX_PROCESS_NUMBER];
/*A pcb's id (pid) is its index in this array*/
static int pcbTableIndex = 0;

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

  pcbTable[++pcbTableIndex] = thrdNode;

  thrdNode->thread.taskID = pcbTableIndex;
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

pcbptr *getPCBFromTable(int index){
  if ((index > 0) && (index < MAX_PROCESS_NUMBER) && pcbTable[index] != NULL )
    return pcbTable[index];
  else{
    printf("Index is not correct!\n");
    return NULL;
  }
}

void delete_proc(pcbptr *thread, queue *que){

  if (thread == NULL){
    printf("Thread is not defined!\n");
  }
  else{
    if (checkQueue(que)){
      pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
      pcbptr *prevThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
      thrdNode = que->front;

      do{
        if (thrdNode->thread.taskID == thread->thread.taskID){
          prevThrdNode->next = thread->next;
        }

        prevThrdNode = thrdNode;
        /* If first note is deleted, change queue front as well. */
        if (thread->thread.taskID == 1){
          que->front = thrdNode->next;
        }
        thrdNode = thrdNode->next;

      }while(thrdNode != NULL);
    }
  }
}

int checkQueue(queue *que){
  if (que->front == NULL)
    return 0; /* If the queue is empty, return 0 */
  else
    return 1; /* else, return a non-zero value*/
}

void displayPCBTable(){
  for (int i = 0; i < MAX_PROCESS_NUMBER; i++){
    if (pcbTable[i] != NULL){
      displayNode(pcbTable[i]);
    }
  }
}

void displayQueue(queue *que){
  if (!checkQueue(que)){
    printf("The queue is empty!\n");
    return;
  }

  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  thrdNode = que->front;

  do{
    displayNode(thrdNode);
    thrdNode = thrdNode->next;
  }while(thrdNode != NULL);

  free(thrdNode);
}

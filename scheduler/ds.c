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

pcbptr *makeProc(int prioritry){

  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));

  if(thrdNode == NULL){
    perror("Unable to allocate thread node");
    exit(1);
  }

  pcbTable[++pcbTableIndex] = thrdNode;

  thrdNode->thread.taskID = pcbTableIndex;
  thrdNode->thread.priority = prioritry;
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

void insert_proc(pcbptr *newThread, queue *que){

  pcbptr *currThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  pcbptr *prevThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  currThrdNode = que->front;

  /*if the queue is empty, just enqueue the process*/
  if(!checkQueue(que)){
    enqueue_proc(newThread, que);
  }
  else{
    do{
      if (newThread->thread.priority > currThrdNode->thread.priority){
        if (currThrdNode == que->front){
          newThread->next = currThrdNode;
          que->front = newThread;
        }
        else{
          newThread->next = currThrdNode;
          prevThrdNode->next = newNode;
        }
        break;
      }

      prevThrdNode = currThrdNode;
      currThrdNode = currThrdNode->next;

    }while(currThrdNode->next != NULL);
    // code here for last node
  }
  return;
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
        /* If first note is deleted, change queue front only. */
        if (thread->thread.taskID == thrdNode->thread.taskID){
          que->front = thrdNode->next;
          break;
        }
        /* If deleted node is not the first one and exists in queue*/
        else if (thrdNode->thread.taskID == thread->thread.taskID){
          prevThrdNode->next = thread->next;
          break;
        }

        prevThrdNode = thrdNode;
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

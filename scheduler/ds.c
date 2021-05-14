#include "ds.h"

static pcbptr *pcbTable[MAX_PROCESS_NUMBER];
/*A pcb's id (pid) is its index in this array*/
static int pcbTableIndex = 0;

queue *createQueue(){

  queue *que = (queue *)malloc(sizeof(struct queue));
  que->front = NULL; que->rear = NULL;

  return que;
}

int findSuitableIndex(){

  for (int i = 1; i < MAX_PROCESS_NUMBER; i++){
    if (pcbTable[i] == NULL)
      return i;
  }

  return -1;
}

pcbptr *makeProc(int prioritry){

  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));

  if(thrdNode == NULL){
    // perror("Unable to allocate thread node");
    exit(1);
  }

  pcbTable[++pcbTableIndex] = thrdNode;

  thrdNode->thread.taskID = pcbTableIndex;
  thrdNode->thread.priority = prioritry;
  thrdNode->thread.dataArea = 111;

  return thrdNode;
}

int makeProc2(int *threadAddress, int prioritry, void (*ftpr)(void *p)){

  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));

  if(thrdNode == NULL){
    perror("Unable to allocate thread node");
    exit(1);
  }

  int pcbTableIndex = -1;
  if ((pcbTableIndex = findSuitableIndex()) == -1 ){
    printf("The process stack is full!\n");
    return -1;
  }
  else{
    pcbTable[pcbTableIndex] = thrdNode;
  }

  *threadAddress = pcbTableIndex;
  thrdNode->thread.taskID = pcbTableIndex;
  thrdNode->thread.priority = prioritry;
  thrdNode->thread.dataArea = 111;
  thrdNode->ftpr = ftpr;

  pthread_t threadTemp;
  pthread_create( &threadTemp, NULL, (void *)thrdNode->ftpr, (void *) NULL);

  return pcbTableIndex;
}

void enqueue_proc(pcbptr *newThread, queue *que){

  if (que->front == NULL){
    que->front = newThread;
    que->rear = newThread;
    que->front->next = NULL;
    que->rear->next = NULL;
  }
  else{
    que->rear->next = newThread;
    que->rear = newThread;
    que->rear->next = NULL;
  }
}

int enqueue_proc2(int pid, queue *que){

  if (que->front == NULL){
    que->front = pcbTable[pid];
    que->rear = pcbTable[pid];
    que->front->next = NULL;
    que->rear->next = NULL;
  }
  else{
    que->rear->next = pcbTable[pid];
    que->rear = pcbTable[pid];
    que->rear->next = NULL;
  }

  return 0;
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
          prevThrdNode->next = newThread;
        }
        return; /* Insertion is done, return.*/
      }

      prevThrdNode = currThrdNode;
      currThrdNode = currThrdNode->next;

    }while(currThrdNode->next != NULL);
    /* new node's priority is not greater than any node. Place it to the rear.*/
    currThrdNode->next = newThread;
    newThread->next = NULL;
    que->rear = newThread;  /* Update rear node. */
  }
  return;
}

int insert_proc2(int pid, queue *que){
  pcbptr *currThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  pcbptr *prevThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  currThrdNode = que->front;

  /*if the queue is empty, just enqueue the process*/
  if(!checkQueue(que)){
    enqueue_proc(pcbTable[pid], que);
  }
  else{
    do{
      if (pcbTable[pid]->thread.priority > currThrdNode->thread.priority){
        if (currThrdNode == que->front){
          pcbTable[pid]->next = currThrdNode;
          que->front = pcbTable[pid];
        }
        else{
          pcbTable[pid]->next = currThrdNode;
          prevThrdNode->next = pcbTable[pid];
        }
        return 0; /* Insertion is done, return.*/
      }

      prevThrdNode = currThrdNode;
      currThrdNode = currThrdNode->next;

    }while(currThrdNode->next != NULL);
    /* new node's priority is not greater than any node. Place it to the rear.*/
    currThrdNode->next = pcbTable[pid];
    pcbTable[pid]->next = NULL;
    que->rear = pcbTable[pid];  /* Update rear node. */
  }

  return 0;
}

void delete_proc(pcbptr *deletedThread, queue *que){

  if (deletedThread == NULL){
    printf("Thread is not defined!\n");
  }
  else{
    if (checkQueue(que)){
      pcbptr *currThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
      pcbptr *prevThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
      currThrdNode = que->front;

      do{
        if (deletedThread->thread.taskID == currThrdNode->thread.taskID){
          /* If first note is deleted, change queue front only. */
          if (que->front == deletedThread){
            que->front = currThrdNode->next;
            return;
          }
          /* If deleted node is not the first one and exists in queue*/
          prevThrdNode->next = deletedThread->next;
          return;
        }

        prevThrdNode = currThrdNode;
        currThrdNode = currThrdNode->next;

      }while(currThrdNode != NULL);
    }
  }
}

int delete_proc2(int pid, queue *que){

  if (pcbTable[pid] == NULL){
    printf("Thread is not defined!\n");
  }
  else{
    if (checkQueue(que)){
      pcbptr *currThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
      pcbptr *prevThrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
      currThrdNode = que->front;

      do{
        if (pcbTable[pid]->thread.taskID == currThrdNode->thread.taskID){
          /* If first note is deleted, change queue front only. */
          if (que->front == pcbTable[pid]){
            que->front = currThrdNode->next;
            return 0;
          }
          /* If deleted node is not the first one and exists in queue*/
          prevThrdNode->next = pcbTable[pid]->next;
          return 0;
        }

        prevThrdNode = currThrdNode;
        currThrdNode = currThrdNode->next;

      }while(currThrdNode != NULL);
    }
  }

  return 0;
}

pcbptr *del_proc(int index, queue *que){
  /* Copy thread's address*/
  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  thrdNode = getPCBFromTable(index);

  /* First delete thread from the queue*/
  delete_proc(getPCBFromTable(index), que);

  /* Then delete thread from pcb_table*/
  pcbTable[index] = NULL;

  /* Return the address in order to free it. */
  return thrdNode;
}

pcbptr *del_proc2(int pid, queue *que){
  /* Copy thread's address*/
  pcbptr *thrdNode = (pcbptr *)malloc(sizeof(struct pcbptr));
  thrdNode = pcbTable[pid];

  /* First delete thread from the queue*/
  delete_proc(thrdNode, que);

  /* Then delete thread from pcb_table*/
  pcbTable[pid] = NULL;

  /* Return the address in order to free it. */
  return thrdNode;
}


int checkQueue(queue *que){
  if (que->front == NULL)
    return 0; /* If the queue is empty, return 0 */
  else
    return 1; /* else, return a non-zero value*/
}

void displayNode(pcbptr *thrdNode){

  printf("Thread No = %d \n", thrdNode->thread.taskID);
  printf("Thread priority = %d \n", thrdNode->thread.priority);
  printf("Thread dataArea = %d \n", thrdNode->thread.dataArea);
  printf("\n");
}

void displayNode2(int pid){

  printf("Thread No = %d \n", pcbTable[pid]->thread.taskID);
  printf("Thread priority = %d \n", pcbTable[pid]->thread.priority);
  printf("Thread dataArea = %d \n", pcbTable[pid]->thread.dataArea);
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

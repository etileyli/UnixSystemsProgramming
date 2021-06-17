#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <semaphore.h>

#define BUF_SIZE 4
#define SHM_KEY 1000

int shmid;
char *ch;

sem_t semWrite;
sem_t semRead;

pthread_mutex_t lock;

void *writeFunction();
void *readFunction();

int main(int argc, char const *argv[]) {

  pthread_t threadWrite, threadRead;

  int retW, retR;

  /* READ FILE CONTENT INTO "buffer"*/
  FILE *fp;
  char *buffer = NULL;
  long length;
  char *filePath = "64BytesFile";

  fp = fopen(filePath, "rb");

  if (fp){
    fseek (fp, 0, SEEK_END);
    length = ftell (fp);
    fseek (fp, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
      fread (buffer, 1, length, fp);
    }
    fclose (fp);
  }

  // printf("%s\n", buffer);

  // Init semWrite
  sem_init(&semWrite , 0, 1);
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      printf("\n mutex init failed\n");
      return 1;
  }

  // Init semRead
  sem_init(&semRead , 0, 0);
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      printf("\n mutex init failed\n");
      return 1;
  }

  for (int i = 0; i < 5; i++){
    retW = pthread_create(&threadWrite, NULL, writeFunction, NULL);
    retR = pthread_create(&threadRead, NULL, readFunction, NULL);

    pthread_join(threadWrite, NULL);
    pthread_join(threadRead, NULL);
  }

  return 0;
}

void *writeFunction(){

  sem_wait(&semWrite);
  pthread_mutex_lock(&lock);

  shmid = shmget(SHM_KEY, BUF_SIZE, 0644|IPC_CREAT);
  if (shmid == -1) {
     perror("Shared memory fault!");
     exit(-1);
  }

  ch = (char*)shmat(shmid, NULL, 0);
  if (ch == (void *) -1) {
     perror("Shared memory attach fault!");
     exit(-2);
  }

  strcpy(ch, "xyzq");

  shmdt(ch);

  printf("Hello Write\n");

  pthread_mutex_unlock(&lock);
  sem_post(&semRead);
}

void *readFunction(){

  sem_wait(&semRead);
  pthread_mutex_lock(&lock);

  shmid = shmget(SHM_KEY, BUF_SIZE, 0644|IPC_CREAT);
  if (shmid == -1) {
     perror("Shared memory fault!");
     exit(-1);
  }

  char *ch = shmat(shmid, NULL, 0);
  char shmArr[BUF_SIZE];

  strncpy(shmArr, ch, BUF_SIZE);

  shmdt(ch);

  printf("%s\n", shmArr);
  printf("Hello Read\n");

  pthread_mutex_unlock(&lock);
  sem_post(&semWrite);
}

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

#define BUF_SIZE 5
#define SHM_KEY 1000

int shmid;
char *ch ;

int getFileSize(char *filePath);
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

  retW = pthread_create(&threadWrite, NULL, writeFunction, NULL);
  retR = pthread_create(&threadRead, NULL, readFunction, NULL);

  pthread_join(threadWrite, NULL);
  pthread_join(threadRead, NULL);

  return 0;
}

// This function gets size of a file
int getFileSize(char *filePath){
  struct stat bufFileSize;

  if (stat(filePath, &bufFileSize) == -1) {
     perror("stat");
     exit(EXIT_FAILURE);
  }

  int fileSize =(int)bufFileSize.st_size;

  return fileSize;
}

void *writeFunction(){

  int shmid = shmget(SHM_KEY, BUF_SIZE, 0644|IPC_CREAT);
  if (shmid == -1) {
     perror("Shared memory fault!");
     exit(-1);
  }

  ch = (char*)shmat(shmid, NULL, 0);
  if (ch == (void *) -1) {
     perror("Shared memory attach fault!");
     exit(-2);
  }

  strcpy(ch, "abcde");

  shmdt(ch);

  printf("Hello Write\n");
}

void *readFunction(){

  int shmid = shmget(SHM_KEY, BUF_SIZE, 0644|IPC_CREAT);
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
}

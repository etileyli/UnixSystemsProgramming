#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

int getFileSize(char *filePath);
void *writeFunction();
void *readFunction();

int main(int argc, char const *argv[]) {

  pthread_t threadWrite, threadRead;

  int retW, retR;

  int fd;
  char *filePath = "64BytesFile";

  if ((fd = open(filePath, O_RDONLY)) == -1)
  {
      perror("Cannot open file");
      exit(1);
  }

  /* READ FILE CONTENT INTO "buffer"*/
  // get size of the file
  int fileSize = getFileSize(filePath);

  // Allocate space as large as file size
  char buffer[(int)fileSize];
  size_t nbytes = sizeof(buffer);
  ssize_t bytes_read;
  bytes_read = read(fd, buffer, nbytes); // Read from file into "buffer"
  // write(STDOUT_FILENO, buffer, 64);
  close(fd);

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
  printf("Hello Write\n");
}

void *readFunction(){
  printf("Hello Read\n");
}

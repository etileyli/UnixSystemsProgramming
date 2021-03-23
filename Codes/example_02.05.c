#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {

  FILE *fp;

  fp = fopen("file.txt", "r");
  // fp = fopen("/etc/passwd", "w");

  if (fp == NULL){
    printf("Error: %s\n", strerror(errno)); // strerror is in string.h
  }


  int fildes = open("file.txt", O_RDONLY); // O_RDONLY in fcntl.h

  if (fildes == -1){
    perror("(perror)Failed to open the file."); // this message is followed by a colon and
                                                // a message string corresponding to value of errno  (stdio.h)
    fprintf(stderr, "Failed to open file descriptor %d: %s\n", fildes, strerror(errno));  // strerror -> string.h
                                                                                          // stderr -> stdio.h (stderr is a file pointer)
  }

  return 0;
}

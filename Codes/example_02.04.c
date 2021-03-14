#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

  // int fildes = open("/etc/passwdd", O_RDONLY);
  int fildes = open("/etc/passwd", O_RDONLY); // O_RDONLY in fcntl.h (https://pubs.opengroup.org/onlinepubs/007904875/functions/open.html)


  if (fildes == -1){
    perror("Failed to open the file.");
  }
  else{
    printf("File is opened.\n");
    if (close(fildes) == -1)
      perror("Failed to close the file.");
    else
      printf("File is closed.\n");
  }

  return 0;
}

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  int fildes;

  if (close(fildes) == -1)
    perror("Failed to close the file.");

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_KEYWORD "exit"

char *readLine(){
  char *buffer = NULL;  // input line
  size_t bufsize = 512; // max size of input line
  size_t charCount;     // character number of input line

  // allocate memory for input line
  buffer = (char *)malloc(bufsize * sizeof(char));
  if( buffer == NULL)
  {
    perror("Unable to allocate buffer");
    exit(1);
  }

  // get number of characters
  charCount = getline(&buffer, &bufsize, stdin);

  // Truncate last newline character
  buffer[charCount - 1] = '\0';

  return buffer;
}

int main(int argc, char const *argv[]) {

  printf("TURKSHELL'e Hosgeldiniz!\n");

  do{
    char *line = readLine();
    printf("Your input is: %s\n", line);

    if (!strcmp(line, EXIT_KEYWORD)){
      printf("GOODBYE MESSAGE!\n");
      free(line);
      break;
    }

  }while(1);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define EXIT_KEYWORD "exit"

int main(int argc, char const *argv[]) {

  printf("TURKSHELL'e Hosgeldiniz!\n");

  s_command *cmd;

  // shell's loop
  do{
    char *line = readLine();
    // printf("Your input is: %s\n", line);

    // parse input command
    cmd = parse(line);

    printf("isBackground = %d; argv = %d\n", cmd->isBackground, cmd->argc);
    int i = 0;
    while (cmd->argv[i]){
      printf("argument[%d]: %s\n",i , cmd->argv[i]);
      i++;
    }

    // check exit condition
    if (!strcmp(line, EXIT_KEYWORD)){
      printf("CIKIYOR!\n");
      free(line); // free allocated memory in readLine function
      break;
    }

  }while(1);

  return 0;
}

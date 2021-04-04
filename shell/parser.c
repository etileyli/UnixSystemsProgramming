#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

// This function parses user command into s_command variables.
s_command *parse(char *myArgv){

  s_command *cmd = (s_command*)malloc(sizeof(s_command));

  const char s[2] = " ";
  char *token;

  cmd->argv = calloc(1, sizeof(char *));

  /* get the first token */
  int i = 0;
  token = strtok(myArgv, s);

  /* walk through other tokens */
  while( token != NULL ) {
     // printf( " %s\n", token );
     cmd->argv[i++] = token;
     cmd->argv = realloc(cmd->argv, sizeof(char *)*(i + 1));
     token = strtok(NULL, s);
  }

  // an extra NULL is required to terminate the array
  cmd->argv[i] = NULL;

  cmd->argc = i;

  // check if the process is background
  if (!strcmp(cmd->argv[i-1], "&"))
    cmd->isBackground = 1;
  else
    cmd->isBackground = 0;

  return cmd;
}

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
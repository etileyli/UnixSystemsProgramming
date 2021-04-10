#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

  // get delimiters if there is one. get first delimiter only.
  int j = 0;
  while (cmd->argv[j]){
    if (!strcmp(cmd->argv[j], ">>")){
      cmd->delim = ">>";
      break;
    }
    else if(!strcmp(cmd->argv[j], ">")){
      cmd->delim = ">";
      break;
    }
    else if(!strcmp(cmd->argv[j], "<")){
      cmd->delim = "<";
      break;
    }
    else if(cmd->argv[j][0] == '-'){
      cmd->delim = cmd->argv[j];
      break;
    }
    else{
      cmd->delim = NULL;
    }
    j++;
  }
  if (cmd->delim == NULL)
    cmd->delimPos = -1;
  else
    cmd->delimPos = j;

  return cmd;
}

// This function reads a line and returns it.
char *readLine(){
  // Returns NULL if a whitespace character si entered to getline()

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

  if (!isspace(buffer[0]))                      // if something is entered.
    buffer[charCount - 1] = '\0';             // Truncate last newline character
  else
    return NULL;

  return buffer;
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

void printFile(int fd, char *sourceFilePath){

  // get size of the file
  int fileSize = getFileSize(sourceFilePath);

  // Allocate space as large as file size
  char buf[(int)fileSize];
  size_t nbytes = sizeof(buf);
  ssize_t bytes_read, bytes_written;
  bytes_read = read(fd, buf, nbytes);									// Read from file
  bytes_written = write(STDOUT_FILENO, buf, nbytes);	// Write to terminal
  printf("\n");
}

int deleteFile(char *filePath){
  printf("Deleting %s\n", filePath);
  if(!access(filePath, F_OK)) {
    // file exists, delete
    if (unlink(filePath) != 0){
      perror("unlink() error");
      return -1;
    }
  }
  else
    printf("File %s does not exist.\n", filePath);

  return 0;
}

void appendToFile(int fdr, int fdw, char *sourceFilePath, char *targetFilePath){
    // get size of the file
    int fileSize = getFileSize(sourceFilePath);

    // Allocate space as large as file size
    char buf[(int)fileSize];
    size_t nbytes = sizeof(buf);
    ssize_t bytes_read, bytes_written;
    bytes_read = read(fdr, buf, nbytes);			// Read from file
    bytes_written = write(fdw, buf, nbytes);	// Write to target file
    printf("\n");
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#include "parser.h"

// This function parses user command into s_command variables.
s_command *parse(char *myArgv, char *s){

  s_command *cmd = (s_command*)malloc(sizeof(s_command));

  // const char s[2] = " ";
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
  // Returns NULL if a whitespace character is entered to getline()

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

  if (!isspace(buffer[0]))                    // if something is entered.
    buffer[charCount - 1] = '\0';             // Truncate last newline character
  else
    return NULL;

  return buffer;
}

void printCurrentDirectory(){
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working dir: %s\n", cwd);
  } else {
      perror("getcwd() error");
      exit(-1);
  }
}

void printContentOfDir(){
  printf("Contents of directory:\n");
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_REG){
         printf("%s\n", dir->d_name);
      }
    }
    closedir(d);
  }
}

void printCmd(s_command *cmd){
  printf("isBackground = %d; argc = %d\n", cmd->isBackground, cmd->argc);
  printf("delim = %s; delimPos = %d\n", cmd->delim, cmd->delimPos);
  int i = 0;
  while (cmd->argv[i]){
    printf("argument[%d]: %s\n",i , cmd->argv[i]);
    i++;
  }
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

void printHeadOfFile(int fd, char *sourceFilePath, int lineCount){
  // get size of the file
  int fileSize = getFileSize(sourceFilePath);

  // Allocate space as large as file size
  char buf[(int)fileSize];
  size_t nbytes = sizeof(buf);
  ssize_t bytes_read, bytes_written;
  bytes_read = read(fd, buf, nbytes);									// Read from file

  int i = 0, j = 0;
  // printf("%2d- ", j++);
  /* While not EOF put all characters in buffer filled from file to terminal.
  Count down each newline character and when entered number of newline is
  reached put character and exit from the loop */
  while(buf[i] != EOF && lineCount > 0){
    putc(buf[i], stdout);
    if (buf[i++] == '\n'){
      // printf("%2d- ", j++);
      lineCount--;
    }
  }
  putc('\n', stdout);
}

int totalLineCount(int fd, char *sourceFilePath){
  // get size of the file
  int fileSize = getFileSize(sourceFilePath);

  // Allocate space as large as file size
  char buf[(int)fileSize];
  size_t nbytes = sizeof(buf);
  ssize_t bytes_read;
  bytes_read = read(fd, buf, nbytes);									// Read from file

  // count number of lines
  int i = 0, totalLineCount = 0;
  while(buf[i] != EOF){
    if (buf[i++] == '\n'){
      totalLineCount++;
    };
  }
  // printf("Total number of lines: %d\n", --totalLineCount);
  return totalLineCount;
}

void printTailOfFile(char *sourceFilePath, int lineCount){

  FILE *fp;
  char *buffer = NULL;
  long length;

  fp = fopen(sourceFilePath, "rb");

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

  // count number of lines
  int i = 0, totalLineCount = 0;
  while(i < length){
    if (buffer[i++] == '\n'){
      ++totalLineCount;
    }
    // putc(buffer[i], stdout);
  }
  // putc('\n', stdout);

  printf("Total Line Count= %d\n", ++totalLineCount);

  i = 0;
  while(i < length){
    if (buffer[i++] == '\n'){
      totalLineCount--;
      // printf("lineCount = %d\n", lineCount);
      // printf("totalLineCount = %d\n", totalLineCount);
    }

    if (lineCount >= totalLineCount){
        putc(buffer[i], stdout);
    }
  }
  putc('\n', stdout);

  // i = 0;
  // while(length > 0){
  //   if (buffer[i++] == '\n'){
  //     // printf("%2d- ", j++);
  //     totalLineCount--;
  //   }
  //   if (lineCount > totalLineCount){
  //       putc(buffer[i], stdout);
  //   }
  // }
  // putc('\n', stdout);
}

int deleteFile(char *filePath){
  // printf("Deleting %s\n", filePath);
  if(!access(filePath, F_OK)) {
    // file exists, delete
    if (unlink(filePath) != 0){
      perror("unlink() error");
      return -1;
    }
  }
  // else
  //   printf("File %s does not exist.\n", filePath);

  return 0;
}

int createDirectory(char *dirPath){

  // printCurrentDirectory();

  DIR* dir = opendir(dirPath);
  if (dir) {
    /* Directory exists. */
    printf("The name \"%s\" is already taken.\n", dirPath);
    closedir(dir);
  } else if (ENOENT == errno) {
    /* Directory does not exist. */
    int dirResult = mkdir(dirPath, 0755);
    if(dirResult != 0){
      printf("Failed to create directory \"%s\".\n", dirPath);
      return -1;
    }
    else{
      // printf("Directory \"%s\" is created.\n", dirPath);
    }
  }else {
      /* opendir() failed for some other reason. */
      printf("The name %s is already taken.\n", dirPath);
  }

  return 0;
}

// This function returns a positive value if entered string is numeric.
int isDigit(char *str){
  while (*str) {
    if (isdigit(*str++) == 0)
      return 0;
  }
  return 1;
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

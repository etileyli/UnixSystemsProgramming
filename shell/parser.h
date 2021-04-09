#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type s_command stores user command's parsed information.
typedef struct s_command{
  int isBackground;
  int argc;
  char **argv;
  char *delim;
  int delimPos;
}s_command;

s_command *parse(char *myArgv);
char *readLine();
int getFileSize(char *filePath);
void printFile(int fd, char *filePath);
void appendToFile(int fdr, int fdw, char *sourceFilePath, char *targetFilePath);

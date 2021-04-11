#include <unistd.h>
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

s_command *parse(char *myArgv, char *s);
char *readLine();
void printCurrentDirectory();
void printContentOfDir();
void printCmd(s_command *cmd);
int getFileSize(char *filePath);
void printFile(int fd, char *filePath);
void printHeadOfFile(int fd, char *sourceFilePath, int lineCount);
int totalLineCount(int fd, char *sourceFilePath);
void printTailOfFile(char *sourceFilePath, int lineCount);
int deleteFile(char *filePath);
int createDirectory(char *dirPath);
int isDigit(char *str);

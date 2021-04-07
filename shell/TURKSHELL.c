#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parser.h"

#define EXIT_KEYWORD "exit"
#define PROMPT ">>> "

static char *builtInCommands[] = {
	"yankı",
	"cd",
	"help"
};
// Count of all built-in commands
static int numOfElements = sizeof(builtInCommands) / sizeof(builtInCommands[0]);

int main(int argc, char const *argv[]) {

  printf("TURKSHELL'e Hosgeldiniz!\n");

  s_command *cmd;

  // shell's loop
  do{
    printf("%s", PROMPT);
    fflush(stdout);

    char *line = readLine();
    // printf("Your input is: %s\n", line);

    // parse input command
    cmd = parse(line);

    // If nothing is entered, continue.
    if (cmd->argv[0] == NULL)
      continue;

    // printf("isBackground = %d; argv = %d\n", cmd->isBackground, cmd->argc);
    // int i = 0;
    // while (cmd->argv[i]){
    //   printf("argument[%d]: %s\n",i , cmd->argv[i]);
    //   i++;
    // }

    // Print all built-in commands
    // for (int i = 0; i < numOfElements; i++){
    //   printf("%s\n", builtInCommands[i]);
    // }

    // First command: yankı
    if(!strcmp(cmd->argv[0], builtInCommands[0])){
      // printf("The command is %s\n", cmd->argv[0]);
      pid_t childPid;
      pid_t mypid;

      mypid = getpid();
      // Fork
      if ((childPid = fork()) < 0){
        perror("error in fork()");
        return -1;
      }
      else if (childPid == 0) {	// in child process
        // printf("I am child %ld, ID = %ld\n", (long)getpid(), (long)getppid());

        // Echo the words entered after 'yankı'
        int j = 1;
        while (cmd->argv[j]){
          printf("%s ",cmd->argv[j]);
          j++;
        }
        printf("\n");

        return 0;
      }
      // parent process
      else{
        wait(&childPid);
        // printf("I am parent %ld, ID = %ld\n", (long)getpid(), (long)getppid());
      }

    }
    else if(!strcmp(cmd->argv[0], builtInCommands[1])){
      printf("The command is %s\n", cmd->argv[0]);
    }
    else if(!strcmp(cmd->argv[0], builtInCommands[2])){
      printf("The command is %s\n", cmd->argv[0]);
    }
    else{
      printf("Command is not in the list!\n");
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

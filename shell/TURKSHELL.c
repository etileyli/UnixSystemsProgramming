#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "parser.h"

#define EXIT_KEYWORD "exit"
#define PROMPT ">>> "

static char *builtInCommands[] = {
	"yankı",
  "bir",
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

    // If nothing is entered, continue.
    if (line == NULL)
			continue;

		// parse input command
    cmd = parse(line);

		// check exit condition
    if (!strcmp(line, EXIT_KEYWORD)){
      printf("CIKIYOR!\n");
      free(line); // free allocated memory in readLine function
      break;
    }

		// Test code
    // printf("isBackground = %d; argv = %d\n", cmd->isBackground, cmd->argc);
    // printf("delim = %s; delimPos = %d\n", cmd->delim, cmd->delimPos);
    // int i = 0;
    // while (cmd->argv[i]){
    //   printf("argument[%d]: %s\n",i , cmd->argv[i]);
    //   i++;
    // }

    // Print all built-in commands
    // for (int i = 0; i < numOfElements; i++){
    //   printf("%s\n", builtInCommands[i]);
    // }

		pid_t childPid;

		// Fork
		if ((childPid = fork()) < 0){
			perror("error in fork()");
			return -1;
		}
		else if (childPid == 0) {	// in child process
			// printf("I'm child %ld, ID = %ld\n", (long)getpid(), (long)getppid());

			/* 0th Test Command *****************************************************/
			// Test command: yankı
			if(!strcmp(cmd->argv[0], builtInCommands[0])){
				int j = 1;
				while (cmd->argv[j]){
					printf("%s ",cmd->argv[j]);
					j++;
				}
				printf("\n");

				return 0;
			}
			/*1st Command ***********************************************************/
			// birleştir (imitates 'cat' command)
			else if(!strcmp(cmd->argv[0], builtInCommands[1])){

				if (cmd->argc == 1){
					printf("The command \"%s\" needs more arguments.\n", cmd->argv[0]);
				}
				else if (cmd->argc == 2){
					/**1st Function of birleştir: Read file contents into stdout**/
					int fd;
					char *filePath = cmd->argv[1];

					if ((fd = open(filePath, O_RDONLY)) == -1)
					{
							perror("Cannot open file");
							exit(1);
					}

					// print file content to terminal
					printFile(fd, filePath);
					close(fd);
				}
				else if (cmd->argc > 2){
					/**2nd Function of birleştir: Read all non-command arguments as
					input files and print their content to terminal.*** */

					for (int i = 0; i < (cmd->argc - 1); i++){
						int fd;
						char *filePath = cmd->argv[i + 1];
						if ((fd = open(filePath, O_RDONLY)) == -1)
						{
								perror("Cannot open file");
								exit(1);
						}

						// print file content to terminal
						printFile(fd, filePath);
						close(fd);
					}
				}

				return 0;
			}
			else if(!strcmp(cmd->argv[0], builtInCommands[2])){
				printf("The command is %s\n", cmd->argv[0]);
				return 0;
			}
			else{
				printf("Command is not in the list!\n");
				return 0;
			}
		}
		else{	// in parent process
			wait(&childPid);
			// printf("I am parent %ld, ID = %ld\n", (long)getpid(), (long)getppid());
		}
  }while(1);

  return 0;
}

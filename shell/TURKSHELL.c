#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "parser.h"

#define EXIT_KEYWORD "exit"
#define PROMPT ">>> "

static char *builtInCommands[] = {
	"yankı",			// imitates echo
  "bir",				// 1st Command: imitates cat
	"dizinYarat",	// 2nd Command: imitates mkdir
	"dizinYaz",		// imitates pwd
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

		// parse input command wrt space character.
    cmd = parse(line, " ");

		// check exit condition
    if (!strcmp(line, EXIT_KEYWORD)){
      printf("CIKIYOR!\n");
      free(line); // free allocated memory in readLine function
      break;
    }

		// Test code
    // printCmd(cmd);

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
      // Helper command: dizinYaz
      else if(!strcmp(cmd->argv[0], builtInCommands[3])){
        printCurrentDirectory();
        printContentOfDir();

        return 0;
      }
			/*1st Command ***********************************************************/
			// bir (imitates 'cat' command)
			else if(!strcmp(cmd->argv[0], builtInCommands[1])){

				if (cmd->argc == 1){
					printf("The command \"%s\" needs more arguments.\n", cmd->argv[0]);
				}
				else if (cmd->argc == 2){
					/**1st Function of bir: Read file contents into stdout**/
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
				else if (cmd->delim == NULL){
					/**2nd Function of bir: Read all non-command arguments as
					input files and print their content to terminal.*** */
					for (int i = 1; i < (cmd->argc); i++){
						int fd;
						char *filePath = cmd->argv[i];
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
				// if (delimiter is >>) and (only one token is fetched after delimiter)
				else if (!strcmp(cmd->delim, ">>") && (cmd->delimPos + 2 == cmd->argc)){
					/**3rd Function of bir: append files into a file.
					Creates destination file if it does not exists.
					Usage: bir file1 ... fileN >> fileTarget */
					// printf("In 3rd Function of \"bir\"\n");

					for (int i = 1; i < cmd->argc; i++){

  					int fdr, fdw;
  					char *filePath = cmd->argv[i];
						// printf("cmd->argv[1] = %s\n", cmd->argv[i]);

            if (i < cmd->delimPos){         // process files before delimiter.
						  if(access(filePath, F_OK)) {
                // file does not exist
                printf("File %s does not exist!\n", filePath);
                exit(1);
              }
              else{
                // file exists. Open source file.
								if ((fdr = open(filePath, O_RDONLY)) == -1)
								{
										perror("Cannot open source file");
										exit(1);
								}
								// printf("source file name: %s\n", filePath);

								// open target file
								char *targetFilePath = cmd->argv[cmd->delimPos + 1];
								if ((fdw = open(targetFilePath, O_CREAT | O_APPEND | O_RDWR, 0777)) == -1)
								{
										perror("Cannot open target file");
										exit(1);
								}

								int fileSize = getFileSize(filePath);

								// Allocate space as large as file size
								char buf[(int)fileSize];
								size_t nbytes = sizeof(buf);
								ssize_t bytes_read, bytes_written;
								bytes_read = read(fdr, buf, nbytes);			// Read from file
								bytes_written = write(fdw, buf, nbytes);	// Write to target file

								// does not work!
								// appendToFile(fdr, fdw, filePath, targetFilePath);

								close(fdw);
								close(fdr);
              }
            }
					}
				}
				else if (!strcmp(cmd->delim, ">") && (cmd->delimPos + 2 == cmd->argc)){
					/**4th Function of bir: copy contents of files sto a target
          file. Deletes target file if it exists. */
					int fdr, fdw;
          char *targetFilePath = cmd->argv[cmd->delimPos + 1];
          if (deleteFile(targetFilePath) == -1){
            printf("Cannot delete target file %s. Quitting\n", targetFilePath);
            exit(1);
          }

					// create target file
					if ((fdw = open(targetFilePath, O_CREAT | O_RDWR, 0777)) == -1)
					{
							perror("Cannot open target file");
							exit(1);
					}
          close(fdw);

					for (int i = 1; i < cmd->argc; i++){

  					char *filePath = cmd->argv[i];
						// printf("cmd->argv[%d] = %s\n", i, cmd->argv[i]);

            if (i < cmd->delimPos){         // process files before delimiter.
						  if(access(filePath, F_OK)) {
                // file does not exist
                printf("File %s does not exist!\n", filePath);
                exit(1);
              }
              else{
                // file exists. Open source file.
								if ((fdr = open(filePath, O_RDONLY)) == -1)
								{
										perror("Cannot open source file");
										exit(1);
								}
								// printf("source file name: %s\n", filePath);

                // open target file
      					if ((fdw = open(targetFilePath, O_APPEND | O_RDWR, 0777)) == -1)
      					{
      							perror("Cannot open target file");
      							exit(1);
      					}

								int fileSize = getFileSize(filePath);

								// Allocate space as large as file size
								char buf[(int)fileSize];
								size_t nbytes = sizeof(buf);
								ssize_t bytes_read, bytes_written;
								bytes_read = read(fdr, buf, nbytes);			// Read from file
								bytes_written = write(fdw, buf, nbytes);	// Write to target file

								// does not work!
								// appendToFile(fdr, fdw, filePath, targetFilePath);

                close(fdr);
								close(fdw);
              }
            }
					}
				}
        else{
          printf("Invalid usage of \"bir\"!\n");
        }
				return 0;
			}
			else if(!strcmp(cmd->argv[0], builtInCommands[2])){
        /*2nd Command *********************************************************/
        //dizin: create directory. Imitates command "mkdir".
				if (cmd->argc == 1){
					printf("The command \"%s\" needs more arguments.\n", cmd->argv[0]);
				}
        else if (cmd->delim == NULL){
  					/**1st Function of dizinYarat: imitates mkdir for multiple folders*/
            for (int i = 1; i < (cmd->argc); i++){
              char *dirPath = cmd->argv[i];
              createDirectory(dirPath);
            }
        }
        else if (!strcmp(cmd->delim, "-p")){
  					/**2nd Function of dizinYarat: mkdir with subfolders.*/
            s_command *cmdDizin = parse(cmd->argv[cmd->delimPos + 1], "/");
            printCmd(cmdDizin);
            for (int i = 0; i < (cmdDizin->argc); i++){
              char *dirPath = cmdDizin->argv[i];
              createDirectory(dirPath);
              // change directory
              if (chdir(dirPath) != 0){
                perror("chdir() to /tmp failed");
                exit(-1);
              }
            }
        }
        else{
          printf("Invalid usage of \"dizin\"!\n");
        }

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

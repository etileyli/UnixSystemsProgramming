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
#include <utime.h>
// #include <sys/random.h>
#include "parser.h"

#define EXIT_KEYWORD "exit"
#define PROMPT ">>> "

static char *builtInCommands[] = {
	"yankı",			// partially imitates echo
  "bir",				// 1st Command: partially imitates cat
	"dizinYarat",	// 2nd Command: partially imitates mkdir
	"baş",        // 3rd Command: partially imitates head
	"son",        // 4th Command: partially imitates tail
	"dosyaYarat", // 5th Command: partially imitates touch
  "tahminOyunu",// 6th Custom Command: A number guessing game.
	"dizinYaz",		// imitates pwd
	"yardım"
};
// Count of all built-in commands
static int numOfElements = sizeof(builtInCommands) / sizeof(builtInCommands[0]);

int main(int argc, char const *argv[]) {

	displayWelcomeMessage();
	// displayHelpMessage();

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

		pid_t childPid;

		// Fork
		if ((childPid = fork()) < 0){
			perror("error in fork()");
			return -1;
		}
		else if (childPid == 0) {	// in child process
			/* Helper Command: yankı ************************************************/
			if(!strcmp(cmd->argv[0], builtInCommands[0])){
				int j = 1;
				while (cmd->argv[j]){
					printf("%s ",cmd->argv[j]);
					j++;
				}
				printf("\n");

				return 0;
			}
      /* Helper command: dizinYaz *********************************************/
      else if(!strcmp(cmd->argv[0], builtInCommands[7])){
        printCurrentDirectory();
        printContentOfDir();

        return 0;
      }
      /* Helper command: yardım ***********************************************/
      else if(!strcmp(cmd->argv[0], builtInCommands[8])){
        displayHelpMessage();

        return 0;
      }
			else if(!strcmp(cmd->argv[0], builtInCommands[1])){
				/*1st Command *********************************************************/
				/* bir partially imitates cat */
				if (cmd->argc == 1){
					printf("\"%s\" komutu için daha fazla argüman gerekiyor.\n", cmd->argv[0]);
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
					/**1st (extended) Function of bir: Read all non-command arguments as
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
                printf("Dosya %s mevcut değil!\n", filePath);
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
					/**4th Function of bir: copy contents of files to a target
          file. Deletes target file if it exists. */
					int fdr, fdw;
          char *targetFilePath = cmd->argv[cmd->delimPos + 1];
          if (deleteFile(targetFilePath) == -1){
            printf("%s hedef dosyası silinmiyor. Çıkıyor.\n", targetFilePath);
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
                printf("Dosya %s mevcut değil!\n", filePath);
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

                close(fdr);
								close(fdw);
              }
            }
					}
				}
        else{
          printf("\"bir\" komutu için hatalı kullanım!\n");
        }
				return 0;
			}
			else if(!strcmp(cmd->argv[0], builtInCommands[2])){
        /*2nd Command *********************************************************/
        //dizinYarat: creates directory. Imitates command "mkdir".
				if (cmd->argc == 1){
					printf("\"%s\" komutu için daha fazla argüman gerekiyor.\n", cmd->argv[0]);
				}
        else if (cmd->delim == NULL){
					/**1st Function of dizinYarat: imitates mkdir for multiple folders*/
          for (int i = 1; i < (cmd->argc); i++){
            char *dirPath = cmd->argv[i];
            createDirectory(dirPath);
          }
        }
        else if (!strcmp(cmd->delim, "-p")){
					/**2nd Function of dizinYarat: mkdir multiple folders with
          subfolders.
          Usage: dizinYarat -p dir1/dir2/dir3 dir4/dir5/dir6 dir7
          Creates all 7 folders with hierarchy entered.
          */

          // for each cmd argv tokens other than command and delimiter:
          for (int i = 2; i < (cmd->argc); i++){

            /*subDirPath:value that holds how many times the directory changes
             when a new subfolder created. It will be used to come back from
             last created subfolder. */
            int subDirDepth = 0;

            char *dirPath = cmd->argv[i];
            // printf("dir name: %s\n", dirPath);

            /* parse token into directory and its subdirectories.
            Split token by '/' character. */
            s_command *cmdDizin = parse(dirPath, "/");
            // printCmd(cmdDizin);
            /* For each token splitted by '/' create new folder under
            its parent folder created on previous iteration.*/
            for (int i = 0; i < (cmdDizin->argc); i++){
              char *dirPathNew = cmdDizin->argv[i];
              // printf("dirPathNew: %s\n", dirPathNew);
              createDirectory(dirPathNew);
              // change directory
              if (chdir(dirPathNew) != 0){
                perror("chdir() failed");
                exit(-1);
              }
              subDirDepth += 1;
            }

						/* Go up subDirDepth times. */
            for (int j = subDirDepth; j > 0; j--){
              if (chdir("..") != 0){
                perror("chdir() failed");
                exit(-1);
              }
            }
          }
        }
        else{
          printf("\"dizinYarat\" komutu için hatalı kullanım!\n");
        }

				return 0;
			}
      else if(!strcmp(cmd->argv[0], builtInCommands[3])){
        /*3rd Command ********************************************************
        baş: imitates command "head" prints a number of first lines of a file
        Usage:
        baş file1	file2 								(first 10 lines)
        baş -n lineCount file1	        (N defines first N lines of the file)
        baş -n lineCount file1 file2    (first N lines of multiple files)
        */

        int lineCount = 10;   // default value

        if (cmd->argc == 1){
          printf("\"%s\" komutu için daha fazla argüman gerekiyor.\n", cmd->argv[0]);
        }
        else if (cmd->delim == NULL){
          /**1st Function of baş: print first 10 lines of input files */

					for (int i = 1; i < cmd->argc; i++){

						int fd;
						char *filePath = cmd->argv[i];

						if ((fd = open(filePath, O_RDONLY)) == -1)
						{
								perror("Cannot open file");
								exit(1);
						}

						printf("==> %s <==\n", filePath);
						// print first lineCount lines of file to terminal
						printHeadOfFile(fd, filePath, lineCount);
						close(fd);
					}
        }
        else if (cmd->argc >= 4 && !strcmp(cmd->delim, "-n")){
					/**2nd Function of baş: print first "lineCount" lines of input files */

          // if parameter after delimiter -n is a number
          if (isDigit(cmd->argv[2])){
            // printf("cmd->argv[2] = %d\n", atoi(cmd->argv[2]));
						lineCount = atoi(cmd->argv[2]);

						for (int i = 3; i < cmd->argc; i++){
							int fd;
							char *filePath = cmd->argv[i];

							if ((fd = open(filePath, O_RDONLY)) == -1)
							{
									perror("Cannot open file");
									exit(1);
							}
							printf("==> %s <==\n", filePath);
							// print first lineCount lines of file to terminal
							printHeadOfFile(fd, filePath, lineCount);
							close(fd);
						}

          }
          else{
            printf("Argüman pozitif bir sayı olmalı: %s\n", cmd->argv[2]);
          }

        }
        else{
          printf("\"baş\" komutu için hatalı kullanım!\n");
        }

        return 0;
      }
      else if(!strcmp(cmd->argv[0], builtInCommands[4])){
        /*4th Command ********************************************************
        son: imitates command "tail" prints a number of first lines of a file
        Usage:
        son file1												(first 10 lines)
        son -n lineCount file1         	(N defines first N lines of the file)
        son -n lineCount file1 file2   	(first N lines of multiple files)
        */

        int lineCount = 10;   // default value

        if (cmd->argc == 1){
          printf("\"%s\" komutu için daha fazla argüman gerekiyor.\n", cmd->argv[0]);
        }
        else if (cmd->delim == NULL){
          /**1st Function of son: print last 10 lines of input files */

					for (int i = 1; i < cmd->argc; i++){

						int fd;
						char *filePath = cmd->argv[i];

						if ((fd = open(filePath, O_RDONLY)) == -1)
						{
								perror("Cannot open file");
								exit(1);
						}

						// print last lineCount lines of file to terminal
						if ((fd = open(filePath, O_RDONLY)) == -1)
						{
								perror("Cannot open file");
								exit(1);
						}

						printf("==> %s <==\n", filePath);
						printTailOfFile(filePath, lineCount);
						close(fd);
					}
        }
        else if (cmd->argc >= 4 && !strcmp(cmd->delim, "-n")){
					/**2nd Function of son: print last "lineCount" lines of input files */
          // if parameter after delimiter -n is a number
          if (isDigit(cmd->argv[2])){
            // printf("cmd->argv[2] = %d\n", atoi(cmd->argv[2]));
						lineCount = atoi(cmd->argv[2]);

						for (int i = 3; i < cmd->argc; i++){
							int fd;
							char *filePath = cmd->argv[i];

							// get line count of file
							if ((fd = open(filePath, O_RDONLY)) == -1)
							{
									perror("Cannot open file");
									exit(1);
							}
							// print last lineCount lines of file to terminal
							if ((fd = open(filePath, O_RDONLY)) == -1)
							{
									perror("Cannot open file");
									exit(1);
							}

							printf("==> %s <==\n", filePath);
							printTailOfFile(filePath, lineCount);
							close(fd);
						}

          }
          else{
						printf("Argüman pozitif bir sayı olmalı: %s\n", cmd->argv[2]);
          }
        }
        else{
					printf("\"son\" komutu için hatalı kullanım!\n");
        }

        return 0;
      }
			else if(!strcmp(cmd->argv[0], builtInCommands[5])){
				/*5th Command ********************************************************
				dosyaYarat:imitates command "touch" partially. Creates empty files
				Usage:
				dosyaYarat file1 file2					(Creates multiple empty files.
																				If file(s) exist refreshes
																				"Date Modified" attribute.)
				*/
				// sleep(3);
				if (cmd->argc == 1){
					printf("\"%s\" komutu için daha fazla argüman gerekiyor.\n", cmd->argv[0]);
				}
				else if (cmd->delim == NULL){
					/*1st Function of dosyaYarat: Creates empty files entered. */
					for (int i = 1; i < cmd->argc; i++){

						int fd;
						char *filePath = cmd->argv[i];

						if(access(filePath, F_OK)) {
							// file does not exist. Create file.
							if ((fd = open(filePath, O_CREAT, 0777)) == -1)
							{
									perror("Cannot create file");
									exit(1);
							}
							close(fd);
						}
						else{
							utime(filePath, NULL);		// Refreshes modification date.
						}
					}
				}
				else{
					printf("\"dosyaYarat\" komutu için hatalı kullanım!\n");
				}
				return 0;
			}
			else if(!strcmp(cmd->argv[0], builtInCommands[6])){

				if(cmd->argc == 3 && isDigit(cmd->argv[1]) && isDigit(cmd->argv[2])){
					guessGame(atoi(cmd->argv[1]), atoi(cmd->argv[2]));
				}
				else{
					printf("\"dosyaYarat\" komutu için hatalı kullanım!\n");
					printf("Lütfen üst sınırı ve tahmin hakkını girin. ");
					printf("Üst sınır 1'den büyük olmalı.\n");
				}
				return 0;
			}
			else{
				printf("Komut listede mevcut değil!\n");
				return 0;
			}
		}
		else{	// in parent process
			/*If "&" is entered at the end of the command it is a background
			process. Parent will not wait for the child. If not, parent should wait
			for the child.*/
			if (!cmd->isBackground){
				wait(&childPid);
			}
		}
  }while(1);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/utsname.h>
#include <errno.h>
#include <pwd.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include "../shell.h"

void execute(char ** command,int numCommands){
	char cwd[1024];
	int i;
	if(strcmp(command[0],"quit")==0){
		exit(0);
	}
	else if(strcmp(command[0],"echo")==0){
		echo(command,numCommands);
	}
	else if(strcmp(command[0],"pwd")==0){
		pwd();
	}
	else if(strcmp(command[0],"pinfo")==0){
		pinfo(command);
	}
	else if(strcmp(command[0],"cd")==0){
		changeDir(command);
	}
	else if(strcmp(command[0],"ls")==0){
		int x = 0;
		int i;
		for(i=1;i<numCommands;i++){
			if(command[i][0]!=45){
				x = i;
				if (command[i]==NULL || strcmp(command[i],"~")==0)
					chdir(HOME);
				else if((int)command[i][0] == 126){
					char temp[1024];
					strcpy(temp,s+last+1);
					chdir(HOME);
					if(chdir(command[i]+2) == -1){
						printf(" %s: no such directory\n", command[i]);
						chdir(temp);
					}
				}
				else{
					if (chdir(command[i]) == -1) {
						printf(" %s: no such directory\n", command[i]);
					}
				}
				break;
			}
		}
		if(x){
			for(i=x;i<numCommands-1;i++){
				strcpy(command[i], command[i+1]);
			}
			command[numCommands-1] = NULL;
			list(command,numCommands-1);
			chdir(s);
		}
		else
			list(command,numCommands);
	}
	else if(strcmp(command[0],"setenv")==0){
		if(numCommands!=3){
			perror("Error: ");
		}
		else{
			setenv(command[1], command[2], 1);
		}
	}
	else if(strcmp(command[0],"unsetenv")==0){
		if(numCommands!=2){
			perror("Error: ");
		}
		else{
			unsetenv(command[1]);
		}
	}
	else if(strcmp(command[0],"jobs")==0){
		jobs(command, numCommands);
	}
	else if(strcmp(command[0],"fg")==0){
		if(numCommands != 2){
			printf("Error: Give correct number of arguments");
		}
		else{
			fg(command, numCommands);
		}
	}
	else if(strcmp(command[0],"kjob")==0){
		kjob(command, numCommands);
	}
	else if(strcmp(command[0],"overkill")==0){
		overkill(command, numCommands);
	}
	else{
		Exec(command,numCommands);
	}
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include <sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<termios.h>
#include<sys/utsname.h>
#include<errno.h>
#include<pwd.h>
#include<dirent.h>
#include<grp.h>
#include<time.h>
#include "../shell.h"

void changeDir(char ** command){
	if (command[1]==NULL || strcmp(command[1],"~")==0)
		chdir(HOME);
	else if((int)command[1][0] == 126){
		char temp[1024];
		strcpy(temp,s+last+1);
		chdir(HOME);
		if(chdir(command[1]+2) == -1){
			printf(" %s: no such directory\n", command[1]);
			chdir(temp);
		}
	}

	else{
		if (chdir(command[1]) == -1) {
			printf(" %s: no such directory\n", command[1]);
		}
	}
}

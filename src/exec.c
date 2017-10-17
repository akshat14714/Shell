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


void Exec(char **command, int numCommands)
{
	bgp=0;
	if(command[1]==NULL)
		bgp = 0;
	else if(strcmp(command[numCommands-1],"&")==0)
	{
		command[numCommands-1] = NULL;
		bgp = 1;
	}

	int status;

	pid_t pid=fork();

	if (pid < 0)
	{
		printf("ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execvp(*command, command) < 0)
		{
			printf("Invalid Command\n");
		}
	}
	else
	{
		if(bgp == 1)
		{
			bg_order[bg_len++] = pid;
			bg_processes[pid] = malloc(1024);
			strcpy(bg_processes[pid], command[0]);
			printf("[%d]\n",pid);
		}
		else
		{
			fg_flag = 1;
			fg_id = pid;
			strcpy(fg_name,command[0]);
			waitpid(pid,&status,0);
			if(strcmp(command[0],"emacs")==0 || strcmp(command[0],"firefox")==0 || strcmp(command[0],"gedit")==0)
				printf("%s with pid %d exited\n",command[0],pid);
		}
	}
}

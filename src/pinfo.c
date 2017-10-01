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


void pinfo(char ** command){
	char procLoc[1024];
	int fileMem;
	char status1[100], status2[100], status[100];
	if(command[1]==NULL){
		char demo[1024];
		pid_t pid;
		pid = getpid();
		printf("pid -- %d\n", pid);
		FILE *mem = fopen("/proc/self/stat", "r");
		fscanf(mem, "%s %s %s", status1, status2, status);
		printf("Process Status -- %s\n", status);
		mem = fopen("/proc/self/statm", "r");
		fscanf(mem, "%d", &fileMem);
		printf("Memory -- %d\n", fileMem);
		strcpy(demo,"/proc/self/exe");
		int length = readlink(demo, procLoc, sizeof(procLoc));
		procLoc[length] = '\0';
		printf("Executable Path -- %s\n",procLoc);
	}
	else{
		char demo[1024];
		printf("pid -- %s\n", command[1]);
		strcpy(demo, "/proc/");
		strcat(demo, command[1]);
		strcat(demo, "/stat");
		FILE *mem = fopen(demo, "r");
		fscanf(mem, "%s %s %s", status1, status2, status);
		printf("Process Status -- %s\n", status);
		strcpy(demo, "/proc/");
		strcat(demo, command[1]);
		strcat(demo, "/statm");
		mem = fopen(demo, "r");
		fscanf(mem, "%d", &fileMem);
		printf("Memory -- %d\n", fileMem);
		strcpy(demo, "/proc/");
		strcat(demo, command[1]);
		strcat(demo, "/exe");
		int length = readlink(demo, procLoc, sizeof(procLoc));
		procLoc[length] = '\0';
		printf("Executable Path -- %s\n",procLoc);
	}
}

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

void list(char ** command,int numCommands){
	int f=0,i;
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	char buf[512],cwd[1024],cmd[1024];
	getcwd(cwd, sizeof(cwd));
	mydir = opendir(cwd);
	strcpy(cmd,command[0]);
	for(i=1;i<numCommands;i++)
		strcat(cmd,command[i]);
	if(strcmp(cmd,"ls-l")==0 ||strcmp(cmd,"ls-la")==0 || strcmp(cmd,"ls-al")==0 ||strcmp(cmd,"ls-l-a")==0 ||strcmp(cmd,"ls-a-l")==0)
		f=1;
	char path[100005];
	int total = 0;
	while((myfile = readdir(mydir)) != NULL){
		int g=0;
		strcpy(path,cwd);
		strcat(path,"/");
		if(strcmp(cmd,""))
			if(myfile->d_name[0] == 46 && (strcmp(cmd,"ls")==0 || strcmp(cmd,"ls-l")==0)){
				sprintf(buf, "%s/%s", path, myfile->d_name);
				stat(buf, &mystat);
				continue;
			}
		struct stat fstat={0};
		strcpy(path,cwd);
		strcat(path,"/");
		strcat(path,myfile->d_name);
		stat(path,&fstat);
		if(S_ISDIR(fstat.st_mode))
			g=1;
		if(f==1){
			if(g==1)
				printf("d");
			else
				printf("-");

			if(fstat.st_mode & S_IRUSR)
				printf("r");
			else
				printf("-");
			if(fstat.st_mode & S_IWUSR)
				printf("w");
			else
				printf("-");
			if(fstat.st_mode & S_IXUSR)
				printf("x");
			else
				printf("-");

			if(fstat.st_mode & S_IRGRP)
				printf("r");
			else
				printf("-");
			if(fstat.st_mode & S_IWGRP)
				printf("w");
			else
				printf("-");
			if(fstat.st_mode & S_IXGRP)
				printf("x");
			else
				printf("-");

			if(fstat.st_mode & S_IROTH)
				printf("r");
			else
				printf("-");
			if(fstat.st_mode & S_IWOTH)
				printf("w");
			else
				printf("-");
			if(fstat.st_mode & S_IXOTH)
				printf("x\t");
			else
				printf("-\t");

			struct passwd *pw = getpwuid(fstat.st_uid);
			struct group  *gr = getgrgid(fstat.st_gid);

			printf("%ld\t",fstat.st_nlink);

			struct tm lt;
			time_t t = mystat.st_mtime;
			localtime_r(&t, &lt);
			char timebuf[80];
			strftime(timebuf, sizeof(timebuf), "%c", &lt);

			printf("%s\t%s\t%s\t", pw->pw_name, gr->gr_name, timebuf);

			strcpy(path,cwd);
			strcat(path,"/");
			sprintf(buf, "%s/%s", path, myfile->d_name);
			stat(buf, &mystat);
			printf("%zu\t",mystat.st_size);
			
			total += mystat.st_blocks;
		}
		if(f==1){
			if(g==1)
				printf(BLUE "%s" RESET "\n" , myfile->d_name);
			else
				printf("%s\n", myfile->d_name);
		}
		else{
			if(g==1)
				printf(BLUE "%s" RESET "\t", myfile->d_name);
			else
				printf("%s\t", myfile->d_name);
		}
	}
	if(f==0)
		e_l;
	if(f==1)
		printf("total %d\n",total/2);
	closedir(mydir);
}

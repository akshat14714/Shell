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

void printPrompt(){
	char hostname[100009];
	register uid_t uid = geteuid();
	register struct passwd *pw = getpwuid(uid);
	gethostname(hostname, sizeof(hostname));
	printf("<%s@%s:",pw->pw_name,hostname);
	getcwd(s, sizeof(s));
	char cur[100009];
	int len=strlen(s);
	int k=0,i;
	if(strstr(s,HOME)!=NULL)
		k = 1;
	if(strcmp(HOME, s)==0)
		printf(BLUE "~" RESET "> ");
	else if(len>last && k==1)
		printf(BLUE "~%s" RESET "> ",s+last);
	else
		printf(BLUE "%s" RESET "> ", s);
}

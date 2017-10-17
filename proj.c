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
#include "shell.h"

void sigint_handler (int sig) {
    printf ("\n");
    printPrompt();
    fflush (stdout);
}

void sigstop_handler(int sig){
    if(fg_id){
        kill(fg_id, SIGTSTP);
        bg_order[bg_len++] = fg_id;
        bg_processes[fg_id] = malloc(1024);
        strcpy(bg_processes[fg_id],fg_name);
        // fg_id = 0;
        kill(fg_id, SIGCONT);
        fg_id = 0;
    }
}

int main()
{
    bg_len = 0;
	getcwd(HOME,sizeof(HOME));
	last=strlen(HOME);
	clrscr();
	signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigstop_handler);
	while(1){
		int semi=0,q=0;
		int semiColon[10001];
		printPrompt(last,HOME);
		memset (line,'\n',max);
		fgets(line,max,stdin);
		int numCommands=1;
		if((command[0] = strtok(line," \n\t")) == NULL)
			continue;
		while((command[numCommands] = strtok(NULL, " \n\t")) != NULL){
			if(strcmp(command[numCommands],";")==0){
				semi=numCommands;
				semiColon[q++]=numCommands;
			}
			numCommands++;
		}
		if(semi!=numCommands-1)
			semiColon[q++]=numCommands;
		int fd0=-1,fd=-1,in=0,out=0,in_num=2048,out_num=2048,i;
		char input[64],output[64],tp[3];
		if(!semi){
			redirect(command,numCommands);
		}
		else{
			int l=0,r,i;
			for(i=0;i<q;i++){
				r=semiColon[i];
				redirect(&command[l],r-l);
				l=r+1;
			}
		}
	}
	return 0;
}

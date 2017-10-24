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

// void sigstop_handler(int sig){
//     if(fg_id){
//         kill(fg_id, SIGTSTP);
//         bg_order[bg_len++] = fg_id;
//         bg_processes[fg_id] = malloc(1024);
//         strcpy(bg_processes[fg_id],fg_name);
//         // fg_id = 0;
//         kill(fg_id, SIGCONT);
//         fg_id = 0;
//     }
// }

int main()
{
	bg_len = 0;
	getcwd(HOME,sizeof(HOME));
	last=strlen(HOME);
	clrscr();
	signal(SIGINT, sigint_handler);	
	// signal(SIGTSTP, sigstop_handler);
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
		int o=0;
		int i,pl=0,pr=0,in=0,out1=0;
		int pCom[1024],moutfd,minfd;
		if(!semi){
			for(int i=0;i<numCommands;i++)
				if(strcmp(command[i],"|")==0)
					pCom[o++]=i;
			pCom[o++]=numCommands;
			if(o!=1){
				minfd = dup(STDIN_FILENO);
				moutfd = dup(STDOUT_FILENO);
				int l=0,z=-1;
				for(int i=0;i<o;i++){
					int r=pCom[i];
					z=execute_with_pipes(&command[l],z,o-1-i,l,r);
					l=r+1;
				}
				dup2(minfd, STDIN_FILENO);
				close(minfd);
			}
			else
				redirect(command,numCommands);
		}
		else{
			int l=0,r,i;
			for(i=0;i<q;i++){
				o=0;
				r=semiColon[i];
				for(int i=l;i<r;i++)
					if(strcmp(command[i],"|")==0)
						pCom[o++]=i;
				pCom[o++]=r-l;
				if(o==1)
					redirect(&command[l],r-l);
				else{
					minfd = dup(STDIN_FILENO);
					moutfd = dup(STDOUT_FILENO);
					int g=l,z=-1;
					for(int i=0;i<o;i++){
						int h=pCom[i];
						z=execute_with_pipes(&command[g],z,o-1-i,g,h);
						g=h+1;
					}
					dup2(minfd, STDIN_FILENO);
					close(minfd);		
				}
				l=r+1;
			}
		}
	}
	return 0;
}

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


void redirect(char ** command,int numCommands){
	int fd0=-1,fd=-1,in=0,out=0,in_num=2048,out_num=2048,i;
	char input[64],output[64],tp[3];
	for(i=0;i<numCommands;i++)
		    {
		        if(strcmp(command[i],"<")==0)
		        {        
		            command[i]=NULL;
		            strcpy(input,command[i+1]);
		            if(in==0){
		            	in=1;
		            	in_num=i;
		            }           
		        }               

		        else if(strcmp(command[i],">")==0 || strcmp(command[i],">>")==0)
		        {   
		        	strcpy(tp,command[i]);   
		            command[i]=NULL;
		            strcpy(output,command[i+1]);
		            if(out==0){
		            	out=1;
		            	out_num=i;
		            }
		        }         
		    }
			if(in==0 && out==0){
				execute(command,numCommands);
				return;
			}
			if(in && out){
				if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
            		perror(input);
            		return;
        		}
        		if(strcmp(tp,">")==0 )
	        		if ((fd = open(output, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) { 
							perror(output);
							return; 
					}
				else
					if ((fd = open(output, O_CREAT|O_WRONLY|O_APPEND, 0644)) < 0) { 
							perror(output);
							return; 
					}

        		int minfd = dup(STDIN_FILENO);
        		dup2(fd0,0);
        		close(fd0);
        		int moutfd = dup(STDOUT_FILENO);
				dup2(fd,1);
				close(fd);
        		execute(command,min(in_num,out_num));
				
				dup2(minfd, STDIN_FILENO);
				dup2(moutfd, STDOUT_FILENO);
				close(minfd);
				close(moutfd);
				return;
			}
			if(in){
				if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
            		perror(input);
            		return;
        		}
        		int minfd = dup(STDIN_FILENO);
        		dup2(fd0,0);
        		close(fd0);
        		execute(command,min(in_num,out_num));
				dup2(minfd, STDIN_FILENO);
				close(minfd);
				return;
			}
			if(out){
				if(strcmp(tp,">")==0 )
	        		if ((fd = open(output, O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) { 
							perror(output);
							return; 
					}
				if(strcmp(tp,">>")==0){
					if ((fd = open(output, O_CREAT|O_WRONLY|O_APPEND, 0644)) < 0) { 
							perror(output);
							return; 
					}
				}
				int moutfd = dup(STDOUT_FILENO);
				dup2(fd,1);
				close(fd);
				execute(command,min(in_num,out_num));
				dup2(moutfd, STDOUT_FILENO);
				close(moutfd);
				return;
			}
}
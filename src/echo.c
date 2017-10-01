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


void echo(char ** command,int numCommands){
    int i;
    for(i=1;i<numCommands;i++){
        int k=0;
        if(command[i][0]==34 || command[i][0]==92)
            k=1;
        if(command[i][strlen(command[i])-1]==34 && strlen(command[i])!=2){
            if(command[i][strlen(command[i])-2]==92)
                command[i][strlen(command[i])-2]=34;
            command[i][strlen(command[i])-1]=32;
        }
        printf("%s ",command[i]+k);
    }
    printf("\n");
}

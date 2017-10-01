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

void jobs (char **command, int numCommands) {
    int i, j = 1;
    char status[10009], status1[10009], status2[10009];
    for (i = 0; i < 32768; i++) {
        if (bg_processes[bg_order[i]]){
            char myproc[10009];
            sprintf(myproc, "%d", bg_order[i]);
            char demo[1024];
            strcpy(demo,"/proc/");
            strcat(demo,myproc);
            strcat(demo,"/stat");
            FILE *mem = fopen(demo, "r");
            fscanf(mem, "%s %s %s", status1, status2, status);
            // printf("Process Status -- %s\n", status);
            if(strcmp(status,"S")==0 || strcmp(status,"R")==0){
                strcpy(status,"Running");
            }
            else{
                strcpy(status,"Stopped");
            }
            printf("[%d] %s %s [%d]\n", j++, status, bg_processes[bg_order[i]], bg_order[i]);
        }
    }
}

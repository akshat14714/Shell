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

void kjob(char **command, int numCommands){
    pid_t pid = get_job_pid(atoi(command[1]));
    if(pid < 0){
        printf("Job %s doesn't exist\n", command[1]);
        return;
    }
    if(bg_processes[pid]){
        if(numCommands != 3){
            perror("Erorr: \n");
            return;
        }
        else{
            kill(pid, atoi(command[2]));
        }
    }
}

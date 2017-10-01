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

void overkill(char **command, int numCommands){
    int i;
    for (i = 0; i < 32768; i++) {
        if (bg_processes[bg_order[i]]){
            kill(bg_order[i], 9);
        }
    }
}

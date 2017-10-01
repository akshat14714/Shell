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

int get_job_pid (int jobid) {
    int i, j = 0;
    for (i = 0; i < 32767 && j != jobid; i++)
        if (bg_processes[bg_order[i]])
            j++;
    if (i == 32767)
        return -1;
    return bg_order[i-1];
}

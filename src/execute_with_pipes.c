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

int execute_with_pipes (char ** command, int input_pipe,int fl,int l,int r) {
	int pipefd[2];
	if(fl)
    	if (pipe(pipefd) < 0) perror("Unable to create pipes");

    int input_fd = -1, output_fd = -1;

    if (input_pipe >= 0) input_fd = input_pipe;
    if(fl)
    	output_fd = pipefd[1];
    pid_t pid = fork(),wpid;
    if (pid > 0) {
        if (input_fd >= 0) close (input_fd);
		if (output_fd >= 0) close (output_fd);
		wait(NULL);
	}
	else if(pid==0){
		if (input_fd >= 0) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd >= 0) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
		}	
		redirect(command,r-l);
		exit(0);	
	}
	else
		perror("fork");
	return pipefd[0];
}
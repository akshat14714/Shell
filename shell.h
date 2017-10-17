#ifndef SHELL_H
#define SHELL_H

#define GREEN   "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define max 1000001
#define limit 1000001
#define e_l printf("\n");
#define err printf("Error\n");
#define clrscr() printf("\e[1;1H\e[2J");
#define min(a,b) (a<b?a:b)

char *command[limit];
char line[max];
int last;
char s[100001];
char HOME[1024];
int bgp, bg_len, fg_id, fg_flag;
char fg_name[109];
int bg_order[32768];
char *bg_processes[32768];

void printPrompt();

int get_job_pid (int jobid);

void pinfo(char ** command);

void changeDir(char ** command);

void list(char ** command,int numCommands);

void Exec(char ** command,int numCommands);

void execute(char ** command,int numCommands);

void pwd();

void echo(char ** command,int numCommands);

void sigint_handler (int sig);

void redirect(char ** command,int numCommands);

void jobs(char ** command,int numCommands);

void fg(char ** command,int numCommands);

void kjob(char ** command,int numCommands);

void overkill(char ** command,int numCommands);

#endif

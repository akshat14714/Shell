shell: \
			proj.o \
			cd.o \
			exec.o \
			execute.o \
			ls.o \
			pinfo.o \
			printPrompt.o \
			pwd.o \
			echo.o \
			redirect.o \
			execute_with_pipes.o \
			jobs.o \
			get_job_pid.o \
			fg.o \
			kjob.o \
			overkill.o
		$(CC) -g -o shell $^
clean:
	@rm -f *.o shell

proj.o: shell.h proj.c
	$(CC) -g -c proj.c

cd.o: shell.h src/cd.c
	$(CC) -g -c src/cd.c

exec.o: shell.h src/exec.c
	$(CC) -g -c src/exec.c

execute.o: shell.h src/execute.c
	$(CC) -g -c src/execute.c

ls.o: shell.h src/ls.c
	$(CC) -g -c src/ls.c

pinfo.o: shell.h src/pinfo.c
	$(CC) -g -c src/pinfo.c

printPrompt.o: shell.h src/printPrompt.c
	$(CC) -g -c src/printPrompt.c

pwd.o: shell.h src/pwd.c
	$(CC) -g -c src/pwd.c

echo.o: shell.h src/cd.c
	$(CC) -g -c src/echo.c
redirect.o: shell.h src/redirect.c
	$(CC) -g -c src/redirect.c

execute_with_pipes.o: shell.h src/execute_with_pipes.c
	$(CC) -g -c src/execute_with_pipes.c

jobs.o: shell.h src/jobs.c
	$(CC) -g -c src/jobs.c

get_job_pid.o: shell.h src/get_job_pid.c
	$(CC) -g -c src/get_job_pid.c

fg.o: shell.h src/fg.c
	$(CC) -g -c src/fg.c

kjob.o: shell.h src/kjob.c
	$(CC) -g -c src/kjob.c

overkill.o: shell.h src/overkill.c
	$(CC) -g -c src/overkill.c
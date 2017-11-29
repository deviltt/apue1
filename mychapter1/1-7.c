#include "apue.h"

void sig_int(int sig_num)
{
	printf("signum: %d\n", sig_num);
}

int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%% ");
//	puts("%% ");	//和printf等效，但是会自动加上换行符
	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");
	while(fgets(buf, MAXLINE, stdin) != NULL){
		if(buf[strlen(buf) -1] == '\n')
			buf[strlen(buf) -1] = 0;
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0){
		execlp(buf, buf, (char *)0);
		err_ret("couldn't execute: %s", buf);
		exit(127);
	}
	if((pid = waitpid(pid, &status, 0)) < 0)
		err_sys("waitpid error");
	printf("%% ");
	}
	exit(0);
}

#include "apue.h"

static void sig_pipe(int sig_num)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

int main(void)
{
	int n, fd1[2], fd2[2];
	pid_t pid;
	char buf[MAXLINE];
	
	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");
	
	if(pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");

	if((pid = fork()) < 0){
		err_sys("fork error");
	}
	else if(pid > 0){
		close(fd1[0]);
		close(fd2[1]);
		while(fgets(buf, MAXLINE, stdin) != NULL){
			n = strlen(buf);
			if(write(fd1[1], buf, n) != n)
				err_sys("write error");
			if((n = read(fd2[0], buf, MAXLINE)) < 0)
				err_sys("read error");
			if(n == 0){
				err_msg("child close pipe");
				break;
			}
			buf[n] = 0;
			if(fputs(buf, stdout) == EOF)
				err_sys("fputs error");
		}
		if(ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);		
	} 
	else{
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0] != STDIN_FILENO){
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error");
			close(fd1[0]);
		}
		if(fd2[1] != STDOUT_FILENO){
			if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error");
			close(fd2[1]);
		}
		if(execlp("./add", "add", (char *)0) < 0)
			err_sys("execlp error");
	}
	exit(0);
}

#include "apue.h"

void sig_alrm(int signo)
{

}

int main()
{
	int n;
	char line[MAXLINE];
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal (SIGALRM) error");
	alarm(10);

	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}

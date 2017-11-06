#include "apue.h"

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
		printf("received sigusr1\n");
	else if(signo == SIGUSR2)
		printf("received sigusr2\n");
	else
		err_dump("received signal %d\n", signo);
}

int main()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR1");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR2");

	for( ; ; )
		pause();
}

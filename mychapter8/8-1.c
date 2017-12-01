#include "apue.h"

int global = 1;

int main()
{
	int a = 2;
	pid_t pid;
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0){
		global++;
		a++;
	} 
	else
		sleep(2);
	printf("ppid = %d, pid = %d, global = %d, a = %d\n",getppid(), getpid(), global, a);
	return 0;
}

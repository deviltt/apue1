#include "apue.h"

int main()
{
	int n, n1, n2;
	char buf[MAXLINE];

	while((n = read(STDIN_FILENO, buf, MAXLINE)) > 0){
		buf[n] = 0;
		if(sscanf(buf, "%d%d", &n1, &n2) == 2){
			sprintf(buf, "%d\n", n1 + n2);	
			n = strlen(buf);
			if(write(STDOUT_FILENO, buf, n) != n)
				err_sys("write error");
		}
		else{
			if(write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_sys("write error");
		}
	}
	exit(0);
}

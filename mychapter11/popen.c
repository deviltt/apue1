#include "apue.h"

int main()
{
	char buf[MAXLINE];
	FILE *fpout;

	if((fpout = popen("./filter", "r")) == NULL)
		err_sys("popen error");
	for( ; ; ){
		fputs("prompt> ", stdout);
		fflush(stdout);
		if(fgets(buf, MAXLINE, fpout) == NULL)
			break;
		if(fputs(buf, stdout) == EOF)
			err_sys("fputs error");
	}
	if(pclose(fpout) == EOF)
		err_sys("pclose error");
	putchar('\n');
	exit(0);
}

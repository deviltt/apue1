#include "apue.h"
#include "sys/wait.h"

#define PAGER "${PAGER:-more}" //环境变量

int main(int argc, char *argv[])
{
	FILE *fpin, *fpout;
	char line[MAXLINE];

	if(argc != 2)
		err_quit("usage: a.out <pathname>");
	if((fpin = fopen(argv[1], "r")) == NULL)	//以只读的方式打开指定文件
		err_sys("can't open %s", argv[1]);	
	
	if((fpout = popen(PAGER, "w")) == NULL)		//文件指针连接到PAGER的标准输入
		err_sys("popen error");
	
	while(fgets(line, MAXLINE, fpin) != NULL){	//获取指定文件的内容
		if(fputs(line, fpout) == EOF)		//将内容通过PAGER的标准输入写入文件
			err_sys("fputs error to pipe");
	}
	if(ferror(fpin))
		err_sys("fgets error");
	if(pclose(fpout) == -1)
		err_sys("pclose error");

	exit(0);
}

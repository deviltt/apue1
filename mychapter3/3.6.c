#include "apue.h"
#include "fcntl.h"

int main()
{
	int fd, n;
	char buf[4096];
	if((fd = open("./3-1.c", O_RDWR | O_APPEND)) == -1)
		err_sys("open error");

	lseek(fd, 5, SEEK_SET);
	if(read(fd, buf, 5) != 5)
		err_sys("read error");
	
	lseek(fd, 1, SEEK_SET);		//重新定位并没有用，写只能从文件尾端，因为O_APPEND表示每次写都追加到文件尾端
	if(write(fd, buf, 5) != 5) 
		err_sys("write error");
	exit(0);
}

#include "apue.h"
#include "fcntl.h"
int main()
{
	int fd;
	
	if((fd = open("file.hole", O_RDWR | O_CREAT | O_TRUNC)) == -1)
		err_sys("open error");

	if(write(fd, "12345", 5)== 5)
		lseek(fd, 1000, SEEK_CUR);

	if(write(fd, "54321", 5) != 5)
		err_sys("write error");
	
	exit(0);
}

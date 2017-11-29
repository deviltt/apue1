// 功能：显示命令行输入的所有目录的信息 

#include "stdio.h"
#include "dirent.h"

int main(int argc, char *argv[])
{
	DIR *dir;
	int i;
	struct dirent *dirp;

	if(argc <= 1){
		printf("usage: ./out <dirname + dirname + ... >\n");
	}
	for(i = 1; i < argc; i++){
		if((dir = opendir(argv[i])) == NULL)
			perror("opendir error");
		while((dirp = readdir(dir)) != NULL)
			printf("dirname:%-8s dirtype:%-8d \n", 
					dirp->d_name, dirp->d_type);
	}
	close(dir);
	return 0;	
}

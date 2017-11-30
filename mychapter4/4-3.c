#include "apue.h"

int main(int argc, char *argv[])
{
	struct stat buf;
 	char *ptr;
	int i;

	for(i = 1; i < argc; i++){
		printf("%s: ", argv[i]);
		if(lstat(argv[i], &buf) == -1){
			err_ret("stat error");
			continue;
		}
		if(S_ISREG(buf.st_mode))
			ptr = "regular";
		else if(S_ISDIR(buf.st_mode))
			ptr = "directory";
		puts(ptr);
	}
	exit(0);
}

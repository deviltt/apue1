#include "apue.h"
#include "pthread.h"

struct foo{
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s",s);
	printf(" structure at 0x%lx\n", (unsigned long)fp);
	printf(" foo.a = %d\n",fp->a);
	printf(" foo.b = %d\n",fp->b);
	printf(" foo.c = %d\n",fp->c);
	printf(" foo.d = %d\n",fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo foo = {1,2,3,4};

	printfoo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
}

void *thr_fn2(void *arg)
{
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
	pthread_exit((void *)0);
}



int main()
{
	int err;       	 	 //返回值
	pthread_t tip1, tip2;	//新创建线程的线程id会被设置成tip所指向的内存单元

	struct foo *fp;

	if((err = pthread_create(&tip1, NULL, thr_fn1, NULL)) != 0)
		err_exit(err, "can't creat pthread 1");
	
	if((err = pthread_join(tip1, (void *)&fp)) != 0)
		err_exit(err, "can't join pthread 1\n");
	sleep(2);

	printf("parent starting second thread\n");
	
	if((err = pthread_create(&tip2, NULL, thr_fn2, NULL)) != 0)
		err_exit(err, "can't creat pthread 2");

	sleep(2);
	
	printfoo("parent:\n",fp);

	exit(0);
}

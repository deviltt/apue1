#include "apue.h"
#include "pthread.h"

void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *thr_fun1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if(arg)
		return ((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return ((void *)1);
}

void *thr_fun2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if(arg)
		return ((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit ((void *)2);
}

int main()
{
	int err;                       	//用来判断出错返回
	pthread_t tid1, tid2;
	
	void *tret;

	if((err = pthread_create(&tid1, NULL, thr_fun1, (void *)1)) != 0)
		err_exit(err, "can't create thread 1");
	
	if((err = pthread_create(&tid2, NULL, thr_fun2, (void *)1)) != 0)
		err_exit(err, "can't create thread 2");

	if((err = pthread_join(tid1, &tret)) != 0)
		err_exit(err, "can't join with thread 1");
	
	printf("thread 1 exit code %ld\n", (long)tret);	

	if((err = pthread_join(tid2, &tret)) != 0)
		err_exit(err, "can't join with thread 2");

	printf("thread 2 exit code %ld\n", (long)tret);	
	
	exit(0);
}

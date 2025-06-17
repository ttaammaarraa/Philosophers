#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void *thread_func(void *arg) {
	printf("Hello from a thread! Argument: %d\n", *(int*)arg);
	sleep(2);
	printf("Thread finished.\n");
	return NULL;
}

int	main(void)
{
	pthread_t threadId;
	int data = 123;
	if (pthread_create(&threadId, NULL, thread_func, &data) != 0) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	printf("Main thread continues...\n");
	if (pthread_join(threadId, NULL) != 0) {
		fprintf(stderr, "Error joining thread\n");
		return 1;
	}
	printf("Main thread finished.\n");
	return (EXIT_SUCCESS);
}

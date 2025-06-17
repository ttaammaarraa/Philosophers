/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_data_race_example.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:00:03 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/17 18:30:24 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct thread_data
{
	int shared_resources;
	pthread_mutex_t print;
	pthread_mutex_t increment;
} t_thread_data;


void *thread_func(void *arg) {
	printf("Hello from a thread! Argument: %d\n", *(int*)arg);
	sleep(2);
	printf("Thread finished.\n");
	return NULL;
}
void *increment_thread(void *arg)
{
	t_thread_data *data = (t_thread_data *) arg;
	  for (int i = 0; i < 25; ++i) {
		pthread_mutex_lock(&data->print);
		pthread_mutex_lock(&data->increment);
		printf("\nshared_resources: %i - %i\n", data->shared_resources, i);
		data->shared_resources++;
		pthread_mutex_unlock(&data->increment);
		pthread_mutex_unlock(&data->print);
	}
	return NULL;
}
void thread_work()
{
	pthread_t thread1, thread2;
	int shared_data = 0;
	t_thread_data thread_data = { 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER	};
	pthread_create(&thread1, NULL, increment_thread, &thread_data);
	pthread_create(&thread2, NULL, increment_thread, &thread_data);
	pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

int	main(void)
{
	thread_work();
	printf("Main thread finished.\n");
	return (EXIT_SUCCESS);
}

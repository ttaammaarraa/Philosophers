/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_race_problem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:00:03 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/17 18:32:33 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void *increment_thread(void *arg)
{
	int* shared_resource = (int*)arg;
	  for (int i = 0; i < 25; ++i) {
		printf("\nshared_resources: %i - %i\n", *shared_resource, i);
		(*shared_resource)++;
	}
	return NULL;
}
void thread_work()
{
	pthread_t thread1, thread2;
	int shared_data = 0;
	pthread_create(&thread1, NULL, increment_thread, &shared_data);
	pthread_create(&thread2, NULL, increment_thread, &shared_data);
	pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

int	main(void)
{
	thread_work();
	return (EXIT_SUCCESS);
}

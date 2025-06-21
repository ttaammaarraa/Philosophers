/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:20:58 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/21 19:37:44 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_struct(t_data *data)
{
	printf("n_p: %i\nttd: %i\ntte: %i\ntts: %i\nmte: %i",
	data->n_philosophers, data->ttd, data->tte, data->tts, data->n_times_eat);
}
void wait_thread(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state);
	while(!philo->data->all_ready)
	{
		pthread_mutex_unlock(&philo->data->state);
		usleep(100);
		pthread_mutex_lock(&philo->data->state);
	}
	pthread_mutex_unlock(&philo->data->state);
}
void *test(void *pdata)
{
	t_philo *philo = (t_philo*)pdata;
	wait_thread(philo);
	printf("\nphilo id %li\n", philo->idthread);
	return (NULL);
}

long long get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void philo_init_state(t_philo *philo)
{
	wait_thread(philo);
	if(philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->meals);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meals);
}

// data->stop_simulation
int is_stopped(t_philo *philo)
{
	int stop;

	stop = 0;
	pthread_mutex_lock(&philo->data->state);
	stop = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->state);
	return (stop);
}

int is_enough(t_philo *philo)
{
	int enough;

	enough = 0;
	pthread_mutex_lock(&philo->mmutex);
	enough = (philo->eating >= philo->data->n_times_eat);
	pthread_mutex_unlock(&philo->mmutex);
	return (enough);
}

int	create_philo_thread(t_data *data)
{
	int index;

	index = 0;
	while (data->n_philosophers > index)
	{
		if(pthread_create(&data->philo[index].idthread, NULL, test, &data->philo[index]) != 0)
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}

int create_monitor_thread(t_data *data)
{
	// if(pthread_create(&data->mid, NULL, test, data) != 0)
	// 	return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int create_thread(t_data *data)
{
	int index;

	index = 0;
	if((create_philo_thread(data) || create_monitor_thread(data)) != 0)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(&data->state);
	data->all_ready = 1;
	pthread_mutex_unlock(&data->state);
	while (data->n_philosophers > index)
	{
		pthread_join(data->philo[index].idthread, NULL);
		index++;
	}
	if(pthread_join(data->mid, NULL) != 0)
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
	
}

int	main(int argc, char **argv)
{
	t_data	data;
	memset(&data, 0, sizeof(t_data));
	if(init_data(&data, argc, argv) || forks_init(&data) || philo_init(&data))
	{
		printf("Error\n");
		clean_up(&data);
		return (EXIT_FAILURE);
	}
	if(!create_thread(&data))
	{
		clean_up(&data);
		return(EXIT_FAILURE);
	}
#ifdef DS
	print_struct(&data);
#endif
	return (EXIT_SUCCESS);
}

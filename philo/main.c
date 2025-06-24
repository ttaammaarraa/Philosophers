/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:20:58 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/24 11:19:16 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_thread(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state);
	while (philo->data->all_ready == 0)
	{
		pthread_mutex_unlock(&philo->data->state);
		usleep(100);
		pthread_mutex_lock(&philo->data->state);
	}
	pthread_mutex_unlock(&philo->data->state);
}

void	philo_init_state(t_philo *philo)
{
	wait_thread(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->mmutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mmutex);
}

int	is_enough(t_philo *philo)
{
	int	enough;

	enough = 0;
	pthread_mutex_lock(&philo->mmutex);
	if (philo->data->n_times_eat != -1)
		enough = (philo->meals >= philo->data->n_times_eat);
	pthread_mutex_unlock(&philo->mmutex);
	return (enough);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv) || forks_init(&data) || philo_init(&data))
	{
		printf("Error\n");
		clean_up(&data);
		return (EXIT_FAILURE);
	}
	if (create_thread(&data))
	{
		clean_up(&data);
		return (EXIT_FAILURE);
	}
	clean_up(&data);
	return (EXIT_SUCCESS);
}

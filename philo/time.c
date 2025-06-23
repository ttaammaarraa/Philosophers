/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:20:04 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/23 13:41:57 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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

long long get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	mili_sleep(long long time)
{
	long long start_time;

	start_time = get_time();
	while((get_time() - start_time) < time)
		usleep(100);
}

int	inter_mili_sleep(t_philo *philo, long long time)
{
	long long start_time;

	start_time = get_time();
	while((get_time() - start_time) < time)
	{
		if(is_stopped(philo))
			return (EXIT_FAILURE);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

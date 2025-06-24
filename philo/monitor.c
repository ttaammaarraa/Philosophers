/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:25:55 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/24 11:58:10 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ate_enough(t_philo *philos)
{
	int	counter;
	int	all_ate_enough;

	counter = 0;
	all_ate_enough = 1;
	pthread_mutex_lock(&philos->data->state);
	if (philos->data->stop_simulation)
	{
		pthread_mutex_unlock(&philos->data->state);
		return (0);
	}
	pthread_mutex_unlock(&philos->data->state);

	while (philos->data->n_philosophers > counter)
	{
		if (is_enough(&philos[counter]) == 0)
		{
			all_ate_enough = 0;
			break ;
		}
		counter++;
	}
	return (all_ate_enough);
}

int	check_dead(t_philo *philo)
{
	long long	current_time;
	int		should_die;

	pthread_mutex_lock(&philo->mmutex);
	current_time = get_time();
	should_die = ((current_time - philo->last_meal_time) >= philo->data->ttd);

	if (should_die)
	{
		pthread_mutex_lock(&philo->data->print);
		pthread_mutex_lock(&philo->data->state);
		if (!philo->data->stop_simulation)
		{
			printf("%lld %i died\n", current_time - philo->data->start_time,
				philo->id);
			philo->data->stop_simulation = 1;
		}
		pthread_mutex_unlock(&philo->data->state);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->mmutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->mmutex);
	return (EXIT_SUCCESS);
}

int	check_all_dead(t_data *data, t_philo *philos)
{
	int	counter;

	counter = 0;
	while (data->n_philosophers > counter)
	{
		if (check_dead(&philos[counter]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		counter++;
	}
	return (EXIT_SUCCESS);
}

void	*monitor(void *arg)
{
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)arg;
	philos = data->philo;
	wait_thread(&philos[0]);
	while (1)
	{
		if (data->n_times_eat != -1)
		{
			if (check_all_ate_enough(philos))
			{
				pthread_mutex_lock(&data->print);
				pthread_mutex_lock(&data->state);
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->state);
				pthread_mutex_unlock(&data->print);
				break ;
			}
		}
		if (check_all_dead(data, philos) == EXIT_FAILURE)
			break ;
		usleep(100);
	}
	return (NULL);
}

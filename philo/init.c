/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:25:52 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/24 11:13:18 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	data->n_philosophers = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->n_times_eat = ft_atoi(argv[5]);
		if (data->n_times_eat < 1 && data->n_times_eat != -1)
			return (EXIT_FAILURE);
	}
	else
		data->n_times_eat = -1;
	if (data->n_philosophers <= 0 || data->ttd <= 0 || data->tte <= 0
		|| data->tts <= 0)
		return (EXIT_FAILURE);
	data->print = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data->state = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data->stop_simulation = 0;
	return (EXIT_SUCCESS);
}

int	forks_init(t_data *data)
{
	int	index;

	index = 0;
	data->forks = malloc(sizeof(t_forks) * data->n_philosophers);
	if (!data->forks)
		return (EXIT_FAILURE);
	memset(data->forks, 0, sizeof(t_forks) * data->n_philosophers);
	while (data->n_philosophers > index)
	{
		data->forks[index].id = index;
		data->forks[index].m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		index++;
	}
	return (EXIT_SUCCESS);
}

int	philo_init(t_data *data)
{
	int	index;

	index = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philosophers);
	if (!data->philo)
		return (EXIT_FAILURE);
	memset(data->philo, 0, sizeof(t_philo) * data->n_philosophers);
	while (data->n_philosophers > index)
	{
		data->philo[index].id = index + 1;
		data->philo[index].mmutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		data->philo[index].data = data;
		data->philo[index].l_fork = &data->forks[index];
		data->philo[index].r_fork = &data->forks[(index + 1)
			% data->n_philosophers];
		data->philo[index].last_meal_time = get_time();
		data->philo[index].meals = 0;
		data->philo[index].eating = 0;
		index++;
	}
	return (EXIT_SUCCESS);
}

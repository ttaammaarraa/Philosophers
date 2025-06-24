/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:17:59 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/24 11:18:35 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_thread(t_data *data)
{
	int	index;

	index = 0;
	while (data->n_philosophers > index)
	{
		if (pthread_create(&data->philo[index].idthread, NULL, philo_rot,
				&data->philo[index]) != 0)
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	create_monitor_thread(t_data *data)
{
	if (pthread_create(&data->mid, NULL, monitor, data) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_thread(t_data *data)
{
	int	index;

	index = 0;
	data->start_time = get_time();
	if ((create_philo_thread(data) || create_monitor_thread(data)) != 0)
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
	if (pthread_join(data->mid, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

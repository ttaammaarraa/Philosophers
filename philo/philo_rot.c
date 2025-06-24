/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rot_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:28:35 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/24 11:29:35 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_rot(t_philo *philo)
{
	t_forks	*first;
	t_forks	*second;

	setup_forks(philo, &first, &second);
	if (acquire_forks(philo, first, second))
		return (EXIT_FAILURE);
	meal_status(philo, 1);
	print_status(philo, "is eating");
	if (inter_mili_sleep(philo, philo->data->tte) == EXIT_FAILURE)
	{
		meal_status(philo, 0);
		pthread_mutex_unlock(&first->m);
		pthread_mutex_unlock(&second->m);
		return (EXIT_FAILURE);
	}
	meal_status(philo, 0);
	pthread_mutex_unlock(&first->m);
	pthread_mutex_unlock(&second->m);
	return (EXIT_SUCCESS);
}

int	sleeping_rot(t_philo *philo)
{
	if (is_stopped(philo))
	{
		return (EXIT_FAILURE);
	}
	print_status(philo, "is sleeping");
	if (inter_mili_sleep(philo, philo->data->tts) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	thinking_rot(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state);
	if (philo->data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->data->state);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->state);
	print_status(philo, "is thinking");
	usleep(500);
	return (EXIT_SUCCESS);
}

void	*philo_rot(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_init_state(philo);
	while (1)
	{
		if (is_stopped(philo))
			break ;
		if (is_enough(philo))
			break ;
		if (eating_rot(philo) || sleeping_rot(philo) || thinking_rot(philo))
			break ;
	}
	return (NULL);
}

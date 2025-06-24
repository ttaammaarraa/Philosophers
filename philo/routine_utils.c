/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:00:12 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/24 11:29:33 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->print);
	if (!is_stopped(philo))
	{
		current_time = get_time() - philo->data->start_time;
		printf("%lld %i %s\n", current_time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	setup_forks(t_philo *philo, t_forks **first, t_forks **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
	}
	else
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
}

int	handle_single_philo(t_philo *philo, t_forks *first_fork)
{
	if (philo->data->n_philosophers == 1)
	{
		pthread_mutex_unlock(&first_fork->m);
		mili_sleep(philo->data->ttd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	acquire_forks(t_philo *philo, t_forks *first, t_forks *second)
{
	pthread_mutex_lock(&first->m);
	if (is_stopped(philo))
	{
		pthread_mutex_unlock(&first->m);
		return (EXIT_FAILURE);
	}
	print_status(philo, "has taken a fork");
	if (handle_single_philo(philo, first) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&second->m);
	if (is_stopped(philo))
	{
		pthread_mutex_unlock(&first->m);
		pthread_mutex_unlock(&second->m);
		return (EXIT_FAILURE);
	}
	print_status(philo, "has taken a fork");
	return (EXIT_SUCCESS);
}

void	meal_status(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->mmutex);
	if (flag)
	{
		philo->eating = 1;
		philo->last_meal_time = get_time();
	}
	else
	{
		philo->eating = 0;
		philo->meals++;
	}
	pthread_mutex_unlock(&philo->mmutex);
}

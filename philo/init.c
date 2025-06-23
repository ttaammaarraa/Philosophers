/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:25:52 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/23 14:03:51 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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
		if(data->n_times_eat < 1 && data->n_times_eat != -1)
			return (EXIT_FAILURE);
	}
	else
		data->n_times_eat = -1;
	if (data->n_philosophers <= 0 || data->ttd <= 0 || data->tte <= 0 || data->tts <= 0)
		return (EXIT_FAILURE);
	data->print = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	data->state = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	data->stop_simulation = 0;
	return (EXIT_SUCCESS);
}
// create an array of structs
// each struct must be represent by id (philosophers number - 1)
// create a mutix inital for them and assigned the id
int	forks_init(t_data *data)
{
	int index;

	index = 0;
	data->forks = malloc(sizeof(t_forks) * data->n_philosophers);
	if(!data->forks)
		return (EXIT_FAILURE);
	memset(data->forks, 0, sizeof(t_forks) * data->n_philosophers);
	while (data->n_philosophers > index)
	{
		data->forks[index].id = index;
		data->forks[index].m = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		index++;
	}
#ifdef DFA
	int idx = 0;
	while(data->n_philosophers > idx)
	{
		printf("the fork id is %i\n", data->forks[idx].id);
		idx++;
	}
#endif
	return (EXIT_SUCCESS);
}

int	philo_init(t_data *data)
{
	int index;

	index = 0;

	data->philo = malloc(sizeof(t_philo) *data->n_philosophers);
	if(!data->philo)
		return(EXIT_FAILURE);
	memset(data->philo, 0, sizeof(t_philo) * data->n_philosophers);
	while (data->n_philosophers > index)
	{
		data->philo[index].id = index + 1;
		data->philo[index].mmutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		data->philo[index].data = data;
		data->philo[index].l_fork = &data->forks[index];
		data ->philo[index].r_fork = &data->forks[(index + 1) % data->n_philosophers];
		data->philo[index].last_meal_time = get_time();
		data->philo[index].meals = 0;
		data->philo[index].eating = 0;
		index++;
	}
#ifdef DPA
	int i = 0;
	while (data->n_philosophers > i)
	{
		printf("the ID is %i \n" , data->philo[i].id);
		i++;
	}
#endif
	return (EXIT_SUCCESS);
}

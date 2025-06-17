/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:20:58 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/17 19:06:10 by taabu-fe         ###   ########.fr       */
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
		data->n_times_eat = ft_atoi(argv[5]);
	else
		data->n_times_eat = -1;
	if (data->n_philosophers <= 0 || data->ttd <= 0 || data->tte <= 0 || data->tts <= 0)
		return (EXIT_FAILURE);
	data->print = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	data->state = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	return (EXIT_SUCCESS);
}

void print_struct(t_data *data)
{
	printf("n_p: %i\nttd: %i\ntte: %i\ntts: %i\nmte: %i",
	data->n_philosophers, data->ttd, data->tte, data->tts, data->n_times_eat);
}
// create an array of structs
// each struct must be represent by id (philosophers number - 1)
// create a mutix inital for them and assigned the id
int	forks_init(t_data *data)
{
	int id;

	id = 0;
	data->forks = malloc(sizeof(t_forks) * data->n_philosophers + 1);
	if(!data->forks)
		return (EXIT_FAILURE);
	while (data->n_philosophers > id)
	{
		data->forks[id].id = id;
		data->forks[id].m = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		id++;
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

int	main(int argc, char **argv)
{
	t_data	data;
	memset(&data, 0, sizeof(t_data));
	if(init_data(&data, argc, argv) || forks_init(&data))
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
#ifdef DS
	print_struct(&data);
#endif
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:20:58 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/17 13:51:15 by taabu-fe         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

void print_struct(t_data *data)
{
	printf("n_p: %i\nttd: %i\ntte: %i\ntts: %i\nmte: %i",
	data->n_philosophers, data->ttd, data->tte, data->tts, data->n_times_eat);
}

int	main(int argc, char **argv)
{
	t_data	data;
	memset(&data, 0, sizeof(t_data));
	if(init_data(&data, argc, argv) == EXIT_FAILURE)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
#ifdef DEBUG
	print_struct(&data);
#endif
	return (EXIT_SUCCESS);
}

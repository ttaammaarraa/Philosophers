#ifndef PHILO_H
# define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <string.h>
//number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
typedef struct s_data
{
    int n_philosophers;
	int	ttd;
	int	tte;
	int	tts;
	int	n_times_eat;
}	t_data;

int	ft_atoi(const char *str);

#endif

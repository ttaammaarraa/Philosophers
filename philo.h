#ifndef PHILO_H
# define PHILO_H

#include<unistd.h>
#include<stdio.h>

typedef struct s_data
{
    int num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

}               t_data;

#endif
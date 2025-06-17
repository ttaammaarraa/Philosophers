#ifndef PHILO_H
# define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <string.h>
#include <pthread.h>
//number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
typedef struct forks t_forks;
typedef struct s_data
{
    int n_philosophers;
	int	ttd;
	int	tte;
	int	tts;
	int	n_times_eat;
	t_forks* forks;
	pthread_mutex_t print;
	pthread_mutex_t state;
}	t_data;

typedef struct forks
{
	pthread_mutex_t m;
	int	id;
} t_forks;

int	ft_atoi(const char *str);

#endif

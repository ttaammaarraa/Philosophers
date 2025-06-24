#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

//number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
typedef struct s_forks t_forks;
typedef struct s_philo t_philo;
typedef struct s_data
{
	int				n_philosophers;
	int				ttd;
	int				tte;
	int				tts;
	pthread_t		mid;
	int				n_times_eat;
	int				all_ready;
	t_forks			*forks;
	t_philo			*philo;
	long long		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	state;
	int				stop_simulation;
}	t_data;

typedef struct s_forks
{
	pthread_mutex_t	m;
	int				id;
}	t_forks;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal_time;
	int				eating;
	t_forks			*r_fork;
	t_forks			*l_fork;
	pthread_mutex_t	mmutex;
	pthread_t		idthread;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);
int			forks_init(t_data *data);
int			philo_init(t_data *data);
void		clean_up(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
int			is_stopped(t_philo *philo);
void		mili_sleep(long long time);
int			inter_mili_sleep(t_philo *philo, long long time);
long long	get_time(void);
void		print_status(t_philo *philo, char *status);
void		setup_forks(t_philo *philo, t_forks **first, t_forks **second);
int			acquire_forks(t_philo *philo, t_forks *first, t_forks *second);
void		meal_status(t_philo *philo, int flag);
int			eating_rot(t_philo *philo);
int			sleeping_rot(t_philo *philo);
int			thinking_rot(t_philo *philo);
void		*philo_rot(void *arg);
void		philo_init_state(t_philo *philo);
void		wait_thread(t_philo *philo);
int			is_enough(t_philo *philo);
void		*monitor(void *arg);

#endif

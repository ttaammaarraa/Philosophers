/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:00:12 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/06/22 16:56:57 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/**
 * todo: init the start time
 */
void print_status(t_philo *philo, char *status)
{
    long long current_time;

    current_time = 0;
    pthread_mutex_lock(&philo->data->print);
    pthread_mutex_lock(&philo->data->state);
    if(!is_stopped(philo))
    {
        current_time = get_time() - philo->data->start_time;
        printf("%lld %i %s\n", current_time, philo->id, status);
    }
    pthread_mutex_lock(&philo->data->state);
    pthread_mutex_unlock(&philo->data->print);
}

void    setup_forks(t_philo *philo, t_forks **first,t_forks **secound)
{
    if(philo->id %2 == 0)
    {
        *first = philo->r_fork;
        *secound = philo->l_fork;
    }
    else
    {
        *first = philo->l_fork;
        *secound = philo->r_fork;
    }
}

int aquire_forks(t_philo *philo, t_forks *first, t_forks *secound)
{
    pthread_mutex_lock(&first->m);
    if(is_stopped(philo))
    {
        pthread_mutex_unlock(&first->m);
        return (EXIT_FAILURE);
    }
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&secound->m);
    if(is_stopped(philo))
    {
        pthread_mutex_unlock(&first->m);
        pthread_mutex_unlock(&secound->m);
        return (EXIT_FAILURE);
    }
    print_status(philo, "has taken a fork");
    return (EXIT_SUCCESS);
}

void    meal_status(t_philo *philo, int flag)
{
    pthread_mutex_lock(&philo->mmutex);
    if(flag)
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
int eating_rot(t_philo *philo)
{
    t_forks *first;
    t_forks *secound;

    setup_forks(philo, &first, &secound);
    if(aquire_forks(philo, first, secound))
        return(EXIT_FAILURE);
    meal_status(philo, 1);
    if(inter_mili_sleep(philo, philo->data->tte) == EXIT_FAILURE)
    {
        meal_status(philo, 0);
        pthread_mutex_unlock(&first->m);
        pthread_mutex_unlock(&secound->m);
        return (EXIT_FAILURE);    
    }
    meal_status(philo, 0);
    pthread_mutex_unlock(&first->m);
    pthread_mutex_unlock(&secound->m);
    return(EXIT_SUCCESS);
}
int sleeping_rot(t_philo *philo)
{
        if(is_stopped(philo))
        {
            return(EXIT_FAILURE);
        }
        print_status(philo, "is sleeping");
        if(inter_mili_sleep(philo, philo->data->tts) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        return (EXIT_SUCCESS);
}
int thinking_rot(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->state);
    if(philo->data->stop_simulation)
    {
        pthread_mutex_unlock(&philo->data->state);
        return (EXIT_FAILURE);
    }
    pthread_mutex_unlock(&philo->data->state);
    print_status(philo, "is thinking");
    usleep(500);
    return(EXIT_SUCCESS);
}
void *philo_rot(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	philo_init_state(philo);
	while(1)
	{
		if(is_stopped(philo))
			break;
		if(is_enough(philo))
			break;
		if(eating_rot(philo) || sleeping_rot(philo) || thinking_rot(philo))
            break;
	}
    return  (NULL);
}
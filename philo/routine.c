/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:35:07 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/30 09:20:01 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    message(TAKE_FORK, philo);
    pthread_mutex_lock(philo->r_fork);
    message(TAKE_FORK, philo);
}

void    drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void    message(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->message_lock);
    printf("%d %s", philo->id, str);
    pthread_mutex_unlock(&philo->message_lock);
}

void    to_eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->lock);
    philo->is_eating = 1;
    philo->last_meal = get_current_time();
    message(EAT, philo);
    philo->meal_counter++;
    usleep(philo->p->time_2_eat * 1000);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->lock);
    drop_forks(philo);
}

void    to_sleep(t_philo *philo)
{
    message(SLEEP, philo);
    usleep(philo->p->time_2_sleep * 1000);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:53:26 by tiima             #+#    #+#             */
/*   Updated: 2024/06/27 13:40:30 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_status    get_status(t_philo *philo)
{
    t_status    haha;

    pthread_mutex_lock(&philo->get_lock);
    haha = philo->status;
    pthread_mutex_unlock(&philo->get_lock);
    return (haha);
}

void    set_status(t_philo *philo, t_status etat)
{
    pthread_mutex_lock(&philo->set_lock);
    philo->status = etat;
    pthread_mutex_unlock(&philo->set_lock);
}

void    message(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->data->data_lock);
    if (!strcmp(str, "IS DIED\n") && get_status(philo) == DIED)
    {
        printf("%llu %i %s", get_current_time() - philo->data->start_time, philo->id, str);
        philo->data->death = 1;
        kill_all_philos(philo->data);
        pthread_mutex_unlock(&philo->data->data_lock);
        return ;
    }
    if (get_status(philo) != DIED)
        printf("%llu %i %s", get_current_time() - philo->data->start_time, philo->id, str);
    pthread_mutex_unlock(&philo->data->data_lock);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->t_eat - 10);
    while (get_status(philo) != DIED && philo->data->death == 0)
    {
        if (get_status(philo) == DIED)
            break;
        if (eating(philo))
            break;
    // printf("hello\n");
        if (get_status(philo) == DIED)
            break;
        if (sleeping(philo))
            break;
        if (get_status(philo) == DIED)
            break;
        if (thinking(philo))
            break;
    }
    return (NULL);
}

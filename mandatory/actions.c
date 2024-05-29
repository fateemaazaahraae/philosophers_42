/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:26:19 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/29 13:43:56 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    printf("%d has taken fork\n", philo->id);
    pthread_mutex_lock(philo->r_fork);
    printf("%d has taken fork\n", philo->id);
}

void    drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->l_fork);
    printf("%d has droped fork\n", philo->id);
    pthread_mutex_unlock(philo->r_fork);
    printf("%d has droped fork\n", philo->id);
}

void *routine(void *data)
{
    t_philo  *philo;

    // printf("hello\n");
    philo = (t_philo *)data;
    /* while (1)
    { */if (philo->id % 2 != 0)
            sleep(4);
        printf("%d is thinking\n", philo->id);
        sleep(2);
        take_forks(philo);
        printf("%d is eating\n", philo->id);
        sleep(2);
        drop_forks(philo);
        printf("%d is sleeping\n", philo->id);
        sleep(2);
    // }
    return (0);
}
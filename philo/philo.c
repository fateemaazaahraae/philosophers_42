/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:28:19 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/29 18:34:58 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *data)
{
    t_philo  *philo;

    philo = (t_philo *)data;
    if (philo->id % 2 != 0)
        usleep(200);
    while (philo->p->death == 0)
    {
        to_eat(philo);
        to_sleep(philo);
        message(THINK, philo);
    }
    return (0);
}

int init_threads(t_data *p)
{
    int i;

    i = -1;
    while (++i < p->philo_num)
        if (pthread_create(&p->philos[i].th, NULL, &routine, &p->philos[i]))
            return (printf("Failed the create the THREADS !\n"));
    i = -1;
    while (++i < p->philo_num)
        if (pthread_join(p->philos[i].th, NULL))
            return(printf("Failed the join THREADS !\n"));
    return (0);
}
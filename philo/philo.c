/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:28:19 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/30 09:28:38 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *observer(void *arg)
{
    t_data      *p;
    int         i;
    u_int64_t   time;

    p = (t_data *)arg;
    while (!p->death)
    {
        i = -1;
        while (++i < p->philo_num)
        {
            pthread_mutex_lock(&p->philos[i].lock);
            time = get_current_time() - p->philos[i].last_meal;
            if (time >= p->time_2_die /* && p->philos[i].is_eating == 0 */)
            {
                message(DIE, &p->philos[i]);
                p->death = 1;
                pthread_mutex_unlock(&p->philos[i].lock);
                return (0);
            }
            pthread_mutex_unlock(&p->philos[i].lock);
            if (p->death)
                break;
        }
    }
    return (0);
}

void    *routine(void *data)
{
    t_philo  *philo;

    philo = (t_philo *)data;
    // if (philo->id % 2 != 0)
    //     usleep(200);
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
    pthread_t thread_observer;

    i = -1;
    if (pthread_create(&thread_observer, NULL, observer, p))
        return (printf("Failed to create the OBSERVER THREAD\n"));
    while (++i < p->philo_num)
        if (pthread_create(&p->philos[i].th, NULL, &routine, &p->philos[i]))
            return (printf("Failed to create the THREADS !\n"));
    i = -1;
    while (++i < p->philo_num)
        if (pthread_join(p->philos[i].th, NULL))
            return(printf("Failed to join THREADS !\n"));
    if (pthread_join(thread_observer, NULL))
         return(printf("Failed to join the OBSERVER THREADS !\n"));
    return (0);
}
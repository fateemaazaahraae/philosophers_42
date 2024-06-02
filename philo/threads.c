/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:56:23 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/02 16:58:37 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    *observer(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    while (data->death_flag == 0)
    {
        pthread_mutex_lock(&data->data_lock);
        if (data->finish >= data->n_philo)
            data->death_flag = 1;
        pthread_mutex_unlock(&data->data_lock);
    }
    return (0);
}

void    *func(void *arg)
{
    t_philo  *philo;
    int     i;

    philo = (t_philo *)arg;
    i = -1;
    while (philo->data->death_flag == 0)
    {
        pthread_mutex_lock(&philo->data->data_lock);
        if (get_current_time() >= philo->time_die && philo->is_eating == 0)
        {
            message(DIED, philo);
            philo->data->death_flag = 1;
        }
        if (philo->eat_count == philo->data->n_meals)
        {
            pthread_mutex_lock(&philo->data->finish_lock);
            philo->data->finish++;
            philo->eat_count++;
            pthread_mutex_unlock(&philo->data->finish_lock);
        }
        pthread_mutex_unlock(&philo->data->data_lock);
    }
    return (0);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    philo->start = get_current_time();
    philo->time_die = get_current_time() + philo->data->t_die;
    if (pthread_create(&philo->th2, NULL, func, philo))
        return ((void *)1);
    if (philo->id % 2 != 0)
        usleep(100);
    while (philo->data->death_flag == 0)
    {
        go_to_eat(philo);
        go_to_sleep(philo);
        message(THINK, philo);
    }
    return (0);
}

int init_threads(t_data *data)
{
    int         i;
    pthread_t   th_observer;

    i = -1;
    while (++i < data->n_philo)
        if (pthread_create(&data->philo[i].th1, NULL, routine, &data->philo[i]))
            return (printf("Error while creating THREADS !\n"));
    if (pthread_create(&th_observer, NULL, observer, data))
        return (printf("Error while creating the OBSERVER THREAD !\n"));
    i = -1;
    while (++i < data->n_philo)
        if (pthread_join(data->philo[i].th1, NULL))
            return (printf("Error while joining THREADS !\n"));
    if (pthread_join(th_observer, NULL))
        return (printf("Error while joining the OBSERVER THREAD !\n"));
    return (0);
}
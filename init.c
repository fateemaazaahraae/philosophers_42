/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:34:52 by tiima             #+#    #+#             */
/*   Updated: 2024/06/27 13:24:15 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int ft_alloc(t_data *data)
{
    data->philo = malloc(sizeof(t_philo) * data->num_philo);
    if (!data->philo)
        return (printf("ERROR WHILE ALLOCATING ARRAY OF PHILOS !!\n"));
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
    if (!data->forks)
        return (printf("ERROR WHILE ALLOCATING ARRAY OF FORKS !!\n"));
    return (0);
}

int init_forks(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philo)
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (printf("ERROR WHILE INITIALIZING FORKS !!\n"));
    if (pthread_mutex_init(&data->data_lock, NULL))
        return (printf("ERROR WHILE INITIALIZE LOCK MUTEX !!\n"));
    return (0);
}

void    init_philo(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philo)
    {
        data->philo[i].data = data;
        data->philo[i].id = i + 1;
        data->philo[i].status = NOTHING;
        data->philo[i].eat_counter = 0;
        data->philo[i].last_eat = get_current_time();
        pthread_mutex_init(&data->philo[i].get_lock, NULL);
        pthread_mutex_init(&data->philo[i].set_lock, NULL);
        pthread_mutex_init(&data->philo[i].lock, NULL);
        pthread_mutex_init(&data->philo[i].mtx, NULL);
        pthread_mutex_init(&data->philo[i].sleep_lock, NULL);
        /* init mutex */
    }
    i = -1;
    while (++i < data->num_philo)
    {
        data->philo[i].l_fork = &data->forks[i];
        data->philo[i].r_fork = &data->forks[(i + 1) % data->num_philo];
    }
}

int init(t_data *data, char **av)
{
    data->death = 0;
    data->num_philo = ft_atoi(av[1]);
    data->t_die = (long long)ft_atoi(av[2]);
    data->t_eat = (long long)ft_atoi(av[3]);
    data->t_sleep = (long long)ft_atoi(av[4]);
    if (av[5])
        data->num_meals = ft_atoi(av[5]);
    else
        data->num_meals = -1;
    if (ft_alloc(data))
        return (1);
    if (init_forks(data))
        return (1);
    init_philo(data);
    return (0);
}

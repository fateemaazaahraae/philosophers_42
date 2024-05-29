/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:41:54 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/29 13:46:53 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_data(t_data *p, char **av, int ac)
{
    p->philo_num = ft_atoi(av[1]);
    p->time_2_die = ft_atoi(av[2]);
    p->time_2_eat = ft_atoi(av[3]);
    p->time_2_sleep = ft_atoi(av[4]);
    if (av[5])
        p->num_of_meals = ft_atoi(av[5]);
    else
        p->num_of_meals = -1;
}

int    init_forks(t_data *p)
{
    int i;

    i = 0;
    while (i < p->philo_num)
    {
        if (pthread_mutex_init(&p->fork[i], NULL))
            return (printf("Failed to init a mutex\n"));
        i++;
    }
    p->philos[0].p = p;
    p->philos[0].l_fork = &p->fork[0];
    p->philos[0].r_fork = &p->fork[p->philo_num - 1];
    i = 1;
    while (i < p->philo_num)
    {
        p->philos[i].p = p;
        p->philos[i].l_fork = &p->fork[i];
        p->philos[i].r_fork = &p->fork[i - 1];
        i++;
    }
    return (0);
}

int    init_philos(t_data *p)
{
    int i;

    i = 0;
    while (i < p->philo_num)
    {
        p->philos[i].id = i;
        if (pthread_create(&p->philos[i].th, NULL, &routine, &p->philos[i]))
            return (printf("Failed the create the thread\n"));
        i++;
    }
    i = 0;
    while (i < p->philo_num)
    {
        if (pthread_join(p->philos[i].th, NULL))
            return(printf("Failed the join thread\n"));
        i++;
    }
    return (0);
}

int allocation(t_data *p)
{
    p->philos = malloc(sizeof(t_philo) * p->philo_num);
    if (!p->philos)
        return(printf("Error while allocating PHILOS\n"));
    p->fork = malloc(sizeof(pthread_mutex_t) * p->philo_num);
    if (!p->fork)
        return(printf("Error while allocating FORKS\n"));
    return (0);
}

int    init_program(t_data *p, char **av, int ac)
{
    init_data(p, av, ac);
    if (allocation(p))
        return (1);
    if (init_forks(p))
        return (1);
    if (init_philos(p))
        return (1);
    return (0);
}

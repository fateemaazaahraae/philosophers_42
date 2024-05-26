/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:41:54 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/26 11:36:15 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_args(t_data *p, char **av, int ac)
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
    // p->philos[0].l_fork = &p->fork[0];
    // p->philos[0].r_fork = &p->fork[p->philo_num - 1];
    // i = 1;
    // while (i < p->philo_num)
    // {
    //     p->philos[i].l_fork = &p->fork[i];
    //     p->philos[i].r_fork = &p->fork[i - 1];
    //     i++;
    // }
    return (0);
}

void *routine(void *data)
{
    t_data  *p;
    int i;

    p = (t_data *)data;
    i = 0;
    while (i < p->philo_num)
    {
        if (p->philos[i].id % 2 != 0)
        {
            printf("%d I'm sleeping", p->philos[i].id);
            sleep(20);
        }
        else
            printf("%d I'm alive\n", p->philos[i].id);
        i++;
    }
}

int    init_philos(t_data *p)
{
    int i;

    i = 0;
    printf("hello\n");
    if (init_forks(p))
        return (1);
    while (i < p->philo_num)
    {
        p->philos[i].id = i;
        if (pthread_create(&p->philos[i].th, NULL, &routine, p))
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
}

int    init_program(t_data *p, char **av, int ac)
{
    init_args(p, av, ac);
    if (init_philos(p))
        return (1);
}

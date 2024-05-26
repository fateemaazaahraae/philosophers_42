/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:41:54 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/26 09:19:06 by tiima            ###   ########.fr       */
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
        p->num_of_meals= -1;
}

int init_philo(t_data *p)
{
    int i;

    i = 0;
    while (i < p->philo_num)
    {
        p->philos[i].id = i;
        if (pthread_create(p->philos[i].th, NULL, routine, p))
        
    }
}

int   init_program(t_data *p, char **av, int ac)
{
    init_args(p, av, ac)
    if (init_philo(p))
        return (1);
}
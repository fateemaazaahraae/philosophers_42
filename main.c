/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:53 by tiima             #+#    #+#             */
/*   Updated: 2024/06/26 14:45:17 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_all(t_data *data)
{
    int i;

    i = 0;
    while (++i < data->num_philo)
    {
        pthread_mutex_destroy(&data->philo[i].get_lock);
        pthread_mutex_destroy(&data->philo[i].set_lock);
        pthread_mutex_destroy(&data->philo[i].lock);
        pthread_mutex_destroy(&data->philo[i].mtx);
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_destroy(&data->data_lock);
    free(data->philo);
    free(data->forks);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ac != 5 && ac != 6)
        return (printf("ENTER 5 OR 6 ARGUMENTS !!\n"));
    if (check_args(av))
        return (1);
    if (init(&data, av))
        return (1);
    if (threads(&data))
        return (1);
    //clean_all(&data);
    return (0);
}

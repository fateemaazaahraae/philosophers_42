/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:53 by tiima             #+#    #+#             */
/*   Updated: 2024/06/30 12:05:44 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_up(t_data *data)
{
    int i;

    i = -1;
    pthread_mutex_destroy(&data->get_lock);
    pthread_mutex_destroy(&data->set_lock);
    pthread_mutex_destroy(&data->eat_lock);
    pthread_mutex_destroy(&data->death_lock);
    while (++i < data->num_philo)
    {
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
    {
        clean_up(&data);
        return (1);
    }
    return (0);
}

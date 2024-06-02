/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:13:42 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/02 18:12:39 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_up(t_data *data)
{
    int i;
    
    i = -1;
    while (++i < data->n_philo)
    {
        pthread_mutex_destroy(data->philo[i].right_fork);
        pthread_mutex_destroy(data->philo[i].left_fork);
        pthread_mutex_destroy(&data->philo[i].lock);
        pthread_mutex_destroy(&data->philo[i].message);
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_destroy(&data->data_lock);
    pthread_mutex_destroy(&data->finish_lock);
    free(data->philo);
    free(data->forks);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ac != 5 && ac != 6)
        return (printf("Enter 5 or 6 arguments\n"));
    if (check_args(av))
        return (1);
    if (init_data(&data, av))
        return (1);
    clean_up(&data);
    return (0);
}
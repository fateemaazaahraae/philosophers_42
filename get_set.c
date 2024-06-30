/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:31:07 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/30 12:34:53 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int get_value(t_data *data)
{
    int i;

    pthread_mutex_lock(&data->death_lock);
    i = data->death;
    pthread_mutex_unlock(&data->death_lock);
    return (i);
}

void    set_value(t_data *data, int i)
{
    pthread_mutex_lock(&data->death_lock);
    data->death = i;
    pthread_mutex_unlock(&data->death_lock);
}

t_status    get_status(t_philo *philo)
{
    t_status    haha;

    pthread_mutex_lock(&philo->data->get_lock);
    haha = philo->status;
    pthread_mutex_unlock(&philo->data->get_lock);
    return (haha);
}

void    set_status(t_philo *philo, t_status etat)
{
    pthread_mutex_lock(&philo->data->set_lock);
    philo->status = etat;
    pthread_mutex_unlock(&philo->data->set_lock);
}
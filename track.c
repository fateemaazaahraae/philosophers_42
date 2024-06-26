/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:51:40 by tiima             #+#    #+#             */
/*   Updated: 2024/06/26 14:01:21 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int is_philo_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->mtx);
    if (get_status(philo) == DIED)
    {
        printf("hello\n");
        pthread_mutex_unlock(&philo->mtx);
        return (1);
    }
    else if (get_status(philo) != EATING && ((get_current_time() - philo->last_eat) >= philo->data->t_die))
    {
        pthread_mutex_unlock(&philo->mtx);
        return (1);
    }
    pthread_mutex_unlock(&philo->mtx);
    return (0);
}

void    kill_all_philos(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philo)
        set_status(&data->philo[i], DIED);
}

void    *check_death(void *arg)
{
    t_data  *data;
    int     i;

    data = (t_data *)arg;
    i = 0;
    while (i < data->num_philo)
    {
        if (is_philo_death(&data->philo[i]) && get_status(&data->philo[i]) != EATING) //modifiet fhad l condition !!
        {
            message("IS DIED\n", &data->philo[i]);
            kill_all_philos(data);
            data->death = 1;
            break ;
        }
        i++;
        if (i == data->num_philo)
            i = 0;
    }
    return (NULL);
}

void    *check_meals(void *arg)
{
    t_data *data;
    int     i;
    int     counter;

    data = (t_data *)arg;
    i = 0;
    counter = 0;
    while (i < data->num_philo)
    {
        if (data->philo[i].eat_counter >= data->num_meals)
            counter++;
        i++;
        if (counter == data->num_philo)
        {
            //kill_all_philos(data);
            data->death = 1;
            break;
        }
        if (i == data->num_philo)
        {
            i = 0;
            counter = 0;
        }
    }
    return (NULL);
}

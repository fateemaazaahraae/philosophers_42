/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:51:40 by tiima             #+#    #+#             */
/*   Updated: 2024/06/30 14:47:07 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int is_philo_death(t_philo *philo)
{
    if (get_status(philo) == DIED)
        return (1);
    pthread_mutex_lock(&philo->data->time_lock);
    if (get_status(philo) != EATING && ((get_current_time() - philo->last_eat) > philo->data->t_die))
    {
        pthread_mutex_unlock(&philo->data->time_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->time_lock);
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
        if (is_philo_death(&data->philo[i])) //modifiet fhad l condition !!
        {
            message("IS DIED\n", &data->philo[i]);
            set_value(data, 1);
            kill_all_philos(data);
            break ;
        }
        i++;
        if (i == data->num_philo)
            i = 0;
        usleep(1000);
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
        pthread_mutex_lock(&data->eat_lock);
        if (data->philo[i].eat_counter >= data->num_meals)
            counter++;
        pthread_mutex_unlock(&data->eat_lock);
        if (counter == data->num_philo)
        {
            kill_all_philos(data);
            set_value(data, 1);
            printf("hhhhhhhhhhhh\n");
            break;
        }
        i++;
        if (i == data->num_philo)
        {
            i = 0;
            counter = 0;
        }
        usleep(1000);
    }
    return (NULL);
}

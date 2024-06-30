/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:53:26 by tiima             #+#    #+#             */
/*   Updated: 2024/06/30 14:46:40 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    message(char *str, t_philo *philo)
{
    if (get_status(philo) == DIED && strcmp(str, "IS DIED\n"))
        return ;
    pthread_mutex_lock(&philo->data->data_lock);
    if (strcmp(str, "IS DIED\n") == 0 && get_status(philo) != DIED)
    {
        printf("h%llu %i %s", get_current_time() - philo->data->start_time, philo->id, str);
        set_value(philo->data, 1);
        set_status(philo, DIED);
        // printf("1ana hna\n");
        pthread_mutex_unlock(&philo->data->data_lock);
        return ;
    }
    if (get_status(philo) == DIED && strcmp(str, "IS DIED\n"))
        return ;
    if (get_status(philo) != DIED)
    {
        // printf("1ana hna\n");
        printf("r%llu %i %s", get_current_time() - philo->data->start_time, philo->id, str);
    }
    pthread_mutex_unlock(&philo->data->data_lock);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->t_eat - 10);
    while (get_status(philo) != DIED && !get_value(philo->data))
    {
        if (get_status(philo) == DIED)
            break;
        if (eating(philo))
            break;
    // printf("hello\n");
        if (get_status(philo) == DIED)
            break;
        if (sleeping(philo))
            break;
        if (get_status(philo) == DIED)
            break;
        if (thinking(philo))
            break;
    }
    return (NULL);
}

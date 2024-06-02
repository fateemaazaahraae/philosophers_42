/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:10:09 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/02 17:00:16 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    message(FORK, philo);
    pthread_mutex_lock(philo->right_fork);
    message(FORK, philo);
}

void    drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    message(char *str, t_philo *philo)
{
    u_int64_t time;

    pthread_mutex_lock(&philo->message);
    time = get_current_time() - philo->start;
    if (strcmp(str, "DIED") == 0 && philo->data->death_flag == 0)
    {
        printf("%llu %d %s", time, philo->id, str);
        philo->data->death_flag = 1;
    }
    if (philo->data->death_flag == 0)
        printf("%llu %d %s", time, philo->id, str);
    pthread_mutex_unlock(&philo->message);
}

void    go_to_eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->lock);
    philo->is_eating = 1;
    philo->time_die = get_current_time() + philo->data->t_die;
    message(EAT, philo);
    philo->eat_count++;
    usleep(philo->data->t_eat * 1000);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->lock);
    drop_forks(philo);
}

void    go_to_sleep(t_philo *philo)
{
    message(SLEEP, philo);
    usleep(philo->data->t_sleep * 1000);
}

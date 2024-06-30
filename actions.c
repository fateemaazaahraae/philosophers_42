/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:07:28 by tiima             #+#    #+#             */
/*   Updated: 2024/06/30 12:46:50 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int take_fork(t_philo *philo)
{
    if (philo->data->num_philo == 1)
    {
        message("HAS TAKEN THE LEFT FORK\n", philo);
        ft_usleep(philo->data->t_die);
        set_status(philo, DIED);
        message("IS DIED\n", philo);
        set_value(philo->data, 1);
        clean_up(philo->data);
        return (1);
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        message("HAS TAKEN THE LEFT FORK\n", philo);
        pthread_mutex_lock(philo->r_fork);
        message("HAS TAKEN THE RIGHT FORK\n", philo);
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        message("HAS TAKEN THE RIGHT FORK\n", philo);
        pthread_mutex_lock(philo->l_fork);
        message("HAS TAKEN THE LEFT FORK\n", philo);
    }
    return (0);
}

int eating(t_philo *philo)
{
    if (take_fork(philo))
        return (1);
    set_status(philo, EATING);
    message("IS EATING\n", philo);
    pthread_mutex_lock(&philo->data->time_lock);
    philo->last_eat = get_current_time();
    pthread_mutex_unlock(&philo->data->time_lock);
    ft_usleep(philo->data->t_eat);
    pthread_mutex_lock(&philo->data->eat_lock);
    if (philo->data->num_meals != -1)
        philo->eat_counter += 1;
    pthread_mutex_unlock(&philo->data->eat_lock);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    return (0);
}

int sleeping(t_philo *philo)
{
    set_status(philo, SLEEPING);
    if (get_status(philo) == DIED)
        return (1);
    message("IS SLEEPING\n", philo);
    ft_usleep(philo->data->t_sleep);
    return (0);
}

int thinking(t_philo *philo)
{
    set_status(philo, THINKING);
    if (get_status(philo) == DIED)
        return (1);
    message("IS THINKING\n", philo);
    return (0);
}

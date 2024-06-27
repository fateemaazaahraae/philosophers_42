/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:07:28 by tiima             #+#    #+#             */
/*   Updated: 2024/06/25 20:36:58 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int eating(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    // printf("hiii\n");
    message("HAS TAKEN THE LEFT FORK\n", philo);
    if (philo->data->num_philo == 1)
    {
        ft_usleep(philo->data->t_die);
        set_status(philo, DIED);
        message("DIED\n", philo);
        pthread_mutex_unlock(philo->l_fork);
        return (1);
    }
    pthread_mutex_lock(philo->r_fork);
    message("HAS TAKEN THE RIGHT FORK\n", philo);
    pthread_mutex_lock(&philo->lock);
    philo->status = EATING;
    philo->eat_counter += 1;
    philo->last_eat = get_current_time();
    pthread_mutex_unlock(&philo->lock);
    message("IS EATING\n", philo);
    ft_usleep(philo->data->t_eat);
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

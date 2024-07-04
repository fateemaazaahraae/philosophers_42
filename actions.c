/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:07:28 by tiima             #+#    #+#             */
/*   Updated: 2024/07/03 12:53:12 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (philo->data->num_philo == 1)
	{
		message("has taken a fork\n", philo);
		ft_usleep(philo->data->t_die, philo);
		set_status(philo, DIED);
		message("died\n", philo);
		set_value(philo->data, 1);
		return (1);
	}
	if (philo->id % 2 == 0 && !get_finish(philo->data))
	{
		pthread_mutex_lock(philo->r_fork);
		message("has taken a fork\n", philo);
		pthread_mutex_lock(philo->l_fork);
		message("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		message("has taken a fork\n", philo);
		pthread_mutex_lock(philo->r_fork);
		message("has taken a fork\n", philo);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (get_finish(philo->data))
		return (1);
	if (take_fork(philo))
		return (1);
	set_status(philo, EATING);
	message("is eating\n", philo);
	pthread_mutex_lock(&philo->data->time_lock);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->data->time_lock);
	ft_usleep(philo->data->t_eat, philo);
	set_eat(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	set_status(philo, SLEEPING);
	if (get_status(philo) == DIED || get_finish(philo->data))
		return (1);
	message("is sleeping\n", philo);
	ft_usleep(philo->data->t_sleep, philo);
	return (0);
}

int	thinking(t_philo *philo)
{
	set_status(philo, THINKING);
	if (get_status(philo) == DIED || get_finish(philo->data))
		return (1);
	message("is thinking\n", philo);
	return (0);
}

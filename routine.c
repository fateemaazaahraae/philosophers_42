/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:53:26 by tiima             #+#    #+#             */
/*   Updated: 2024/07/03 12:53:37 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_philo *philo)
{
	if (get_finish(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->data_lock);
	if (!get_finish(philo->data) && !get_value(philo->data))
		printf("%llu %i %s", get_current_time() - philo->data->start_time,
			philo->id, str);
	pthread_mutex_unlock(&philo->data->data_lock);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->t_eat - 20, philo);
	while (get_status(philo) != DIED && !get_value(philo->data)
		&& !get_finish(philo->data))
	{
		if (get_status(philo) == DIED || get_finish(philo->data))
			break ;
		if (eating(philo) || get_finish(philo->data))
			break ;
		if (get_status(philo) == DIED || get_finish(philo->data))
			break ;
		if (sleeping(philo) || get_finish(philo->data))
			break ;
		if (get_status(philo) == DIED || get_finish(philo->data))
			break ;
		if (thinking(philo) || get_finish(philo->data))
			break ;
		if (get_status(philo) == DIED || get_finish(philo->data))
			break ;
	}
	return (NULL);
}

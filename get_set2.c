/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:50:17 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/30 19:55:58 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	get_finish(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->finish_lock);
	i = data->finished;
	pthread_mutex_unlock(&data->finish_lock);
	return (i);
}

void	set_finish(t_data *data, int i)
{
	pthread_mutex_lock(&data->finish_lock);
	data->finished = i;
	pthread_mutex_unlock(&data->finish_lock);
}

int	get_eat(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->eat_lock);
	i = philo->eat_counter;
	pthread_mutex_unlock(&philo->data->eat_lock);
	return (i);
}

void	set_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->eat_counter++;
	pthread_mutex_unlock(&philo->data->eat_lock);
}
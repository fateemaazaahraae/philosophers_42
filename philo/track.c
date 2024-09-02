/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:51:40 by tiima             #+#    #+#             */
/*   Updated: 2024/07/01 10:32:53 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_death(t_philo *philo)
{
	if (get_status(philo) == DIED)
		return (1);
	pthread_mutex_lock(&philo->data->time_lock);
	if (get_status(philo) != EATING && ((get_current_time()
				- philo->last_eat) > philo->data->t_die))
	{
		pthread_mutex_unlock(&philo->data->time_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->time_lock);
	return (0);
}

void	kill_all_philos(t_data *data)
{
	int	i;

	i = -1;
	set_value(data, 1);
	while (++i < data->num_philo)
		set_status(&data->philo[i], DIED);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->num_philo)
	{
		if (is_philo_death(&data->philo[i]))
		{
			message("died\n", &data->philo[i]);
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

void	*check_meals(void *arg)
{
	t_data	*data;
	int		i;
	int		counter;

	data = (t_data *)arg;
	i = -1;
	counter = 0;
	while (++i < data->num_philo && !get_value(data))
	{
		if (get_eat(&data->philo[i]) >= data->num_meals)
			counter++;
		if (counter == data->num_philo)
		{
			set_finish(data, 1);
			kill_all_philos(data);
			break ;
		}
		if (i == data->num_philo - 1)
		{
			i = -1;
			counter = 0;
		}
		usleep(1000);
	}
	return (NULL);
}

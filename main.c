/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:53 by tiima             #+#    #+#             */
/*   Updated: 2024/07/03 12:57:28 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->status_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->death_lock);
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->data_lock);
	free(data->philo);
	free(data->forks);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parcing(ac, av))
		return (1);
	if (init(&data, av))
		return (1);
	if (threads(&data))
	{
		clean_up(&data);
		return (1);
	}
	return (0);
}
// last modification : zedt wa7ed chert f ft_usleep cuz of ./philo 3 300 100 8888888 !!!

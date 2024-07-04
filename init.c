/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:34:52 by tiima             #+#    #+#             */
/*   Updated: 2024/07/01 11:20:55 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("ERROR WHILE INITIALIZING FORKS !!\n"));
	if (pthread_mutex_init(&data->data_lock, NULL))
	{
		i = -1;
		while (++i < data->num_philo)
			pthread_mutex_destroy(&data->forks[i]);
		return (printf("ERROR WHILE INITIALIZE LOCK MUTEX !!\n"));
	}
	pthread_mutex_init(&data->status_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->data_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->time_lock, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	set_value(data, 0);
	set_finish(data, 0);
	while (++i < data->num_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].status = NOTHING;
		data->philo[i].eat_counter = 0;
		data->philo[i].last_eat = get_current_time();
	}
	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->num_philo];
	}
}

int	init(t_data *data, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (data->num_philo < 0 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0)
		return (printf("Error\n"));
	if (av[5])
	{
		data->num_meals = ft_atoi(av[5]);
		if (data->num_meals == 0)
			return (printf("Error\n"));
	}
	else
		data->num_meals = -1;
	if (init_forks(data))
		return (free(data->forks), free(data->philo), 1);
	init_philo(data);
	return (0);
}

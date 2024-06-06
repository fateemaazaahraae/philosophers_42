/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:30:45 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/05 16:30:36 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	store_data(t_data *data, char **av)
{
	data->finish = 0;
	data->n_philo = (unsigned long long)ft_atoi(av[1]);
	data->t_die = (unsigned long long)ft_atoi(av[2]);
	data->t_eat = (unsigned long long)ft_atoi(av[3]);
	data->t_sleep = (unsigned long long)ft_atoi(av[4]);
	data->death_flag = 0;
	if (av[5])
		data->n_meals = ft_atoi(av[5]);
	else
		data->n_meals = -1;
	return (0);
}

int	ft_alloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (printf("Error while allocating for PHILO !\n"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (printf("Error while allocating for FORKS !\n"));
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&data->philo[i].lock, NULL))
			return (printf("Error while initializing LOCK MUTEX !\n"));
		if (pthread_mutex_init(&data->philo[i].message, NULL))
			return (printf("Error while initializing MESSAGE MUTEX !\n"));
	}
	i = -1;
	while (++i < data->n_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("Error while initializing FORK MUTEX !\n"));
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->n_philo];
	}
	if (pthread_mutex_init(&data->data_lock, NULL))
		return (printf("Error while initializing DATA_LOCK MUTEX !\n"));
	if (pthread_mutex_init(&data->finish_lock, NULL))
		return (printf("Error while initializing FINISH_LOCK MUTEX !\n"));
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].eat_count = 0;
		data->philo[i].is_eating = 0;
	}
}

int	init_data(t_data *data, char **av)
{
	if (store_data(data, av))
		return (1);
	if (ft_alloc(data))
		return (1);
	if (init_mutex(data))
		return (1);
	init_philos(data);
	if (init_threads(data))
		return (1);
	return (0);
}

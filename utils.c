/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:26:01 by fbazaz            #+#    #+#             */
/*   Updated: 2024/07/03 12:52:26 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	long long	start;

	start = get_current_time();
	while ((size_t)(get_current_time() - start) < milliseconds)
	{
		if (get_status(philo) == DIED || get_finish(philo->data))
			return (1);
		usleep(100);
	}
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("Error to gettime of day\n"));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if ((res * sign) >= INT_MAX || (res * sign) <= INT_MIN)
			return (-42);
		i++;
	}
	return (res * sign);
}

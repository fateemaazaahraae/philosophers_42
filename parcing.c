/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:19 by tiima             #+#    #+#             */
/*   Updated: 2024/07/01 10:18:29 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+'
			&& str[i] != ' ' && str[i] != '\t')
			return (printf("Error\n"));
		if ((str[i] == ' ' || str[i] == '\t') && (i != 0 && str[i + 1] && str[i - 1] != '\t' && str[i - 1] != ' '))
			return (printf("Error\n"));
		i++;
	}
	return (0);
}

int	check_sign(char *str)
{
	int	i;
	int	plus;

	i = 0;
	plus = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				return (printf("Error\n"));
			if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9'
				&& i == 0)
				plus++;
			else
				return (printf("Error\n"));
			if (str[i + 1] == '\0' || i != 0 || plus > 1)
				return (printf("Error\n"));
		}
		i++;
	}
	return (0);
}

int	parcing(int ac, char **av)
{
	int	i;

	if (!(ac == 5 || ac == 6))
		return (printf("Error, enter 5 or 6 arguments\n"));
	i = 1;
	while (i < ac)
	{
		if (check_digit(av[i]) || check_sign(av[i]))
			return (1);
		i++;
	}
	return (0);
}

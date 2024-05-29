/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:31:57 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/22 09:14:41 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	result;
	int		sign;
	
	i = 0;
	result = 0;
	sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

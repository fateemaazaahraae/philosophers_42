/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:23:57 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/02 10:30:19 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int ft_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int check_args(char **av)
{
    if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0 || ft_check(av[1]))
        return (printf("Invalid NUMBER OF PHILOSOPHERS\n"));
    if (ft_atoi(av[2]) <= 0 || ft_check(av[2]))
        return (printf("Invalid TIME TO DIE\n"));
    if (ft_atoi(av[3]) <= 0 || ft_check(av[3]))
        return (printf("Invalid TIME TO EAT\n"));
    if (ft_atoi(av[4]) <= 0 || ft_check(av[4]))
        return (printf("Invalid TIME TO SLEEP\n"));
    if (av[5] && (ft_atoi(av[5]) < 0 || ft_check(av[5])))
        return (printf("Invalid NUMBER OF MEALS\n"));
    return (0);
}
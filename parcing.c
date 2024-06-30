/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:19 by tiima             #+#    #+#             */
/*   Updated: 2024/06/29 14:53:59 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    /* int     i;
    int     j;
    char    **arg;

    i = 1;
    while (av[i])
    {
        arg = ft_split(av[i], ' ');
        if (!arg || !arg[0])
            printf("INVALID ARGUMENT !!\n");
        j = 0;
        while (arg[j]){}
    }
 */

    if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0 || ft_check(av[1]))
        return (printf("INVALID NUM OF PHILOSOPHERS !!\n"));
    if (ft_atoi(av[2]) < 0 || ft_check(av[2]))
        return (printf("INVALID TIME TO DIE !!\n"));
    if (ft_atoi(av[3]) < 0 || ft_check(av[3]))
        return (printf("INVALID TIME TO EAT !!\n"));
    if (ft_atoi(av[4]) < 0 || ft_check(av[4]))
        return (printf("INVALID TIME TO SLEEP !!\n"));
    if (av[5] && (ft_atoi(av[5]) < 0 || ft_check(av[5])))
        return (printf("INVALID NUM OF MEALS !!\n"));
    return (0);
}
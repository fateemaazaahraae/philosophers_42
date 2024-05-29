/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:38 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/26 11:20:14 by tiima            ###   ########.fr       */
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

int    check_args(char **av)
{
    if (ft_atoi(av[1]) > PHILO_NUM || ft_atoi(av[1]) <= 0 || ft_check(av[1]))
        return(printf("Invalid number of philosophers\n"));
    if (ft_atoi(av[2]) <= 0 || ft_check(av[2]))
        return(printf("Invalid time to die\n"));
    if (ft_atoi(av[3]) <= 0 || ft_check(av[3]))
        return(printf("Invalid time to eat\n"));
    if (ft_atoi(av[4]) <= 0 || ft_check(av[4]))
        return(printf("Invalid time to sleep\n"));
    if ( av[5] && (ft_atoi(av[5]) < 0 || ft_check(av[5])))
        return(printf("Invalid number of meals each philosopher must eat\n"));
    return (0);
}

int main(int ac, char **av)
{
    t_data p;

    if (ac != 5 && ac != 6)
        return(printf("Enter 5 or 6 arguments\n"));
    if (check_args(av))
        return (1);
    if (init_program(&p, av, ac))
        return (1);
    return (0);
}
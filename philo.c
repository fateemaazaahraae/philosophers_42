/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:38 by fbazaz            #+#    #+#             */
/*   Updated: 2024/05/22 09:13:49 by fbazaz           ###   ########.fr       */
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

void    check_args(char **av)
{
    if (ft_atoi(av[1]) > PHILO_NUM || ft_atoi(av[1]) <= 0 || ft_check(av[1]))
        ft_putstr("Invalid number of philosophers\n", 1);
    if (ft_atoi(av[2]) <= 0 || ft_check(av[2]))
        ft_putstr("Invalid time to die\n", 1);
    if (ft_atoi(av[3]) <= 0 || ft_check(av[3]))
        ft_putstr("Invalid time to eat\n", 1);
    if (ft_atoi(av[4]) <= 0 || ft_check(av[4]))
        ft_putstr("Invalid time to sleep\n", 1);
    if ( av[5] && (ft_atoi(av[5]) < 0 || ft_check(av[5])))
        ft_putstr("Invalid number of meals each philosopher must eat\n", 1);
    
}

int main(int ac, char **av)
{
    t_philo p;

    if (ac != 5 && ac != 6)
        ft_putstr("Enter 5 or 6 arguments\n", 1);
    check_args(av);
    return (0);
}
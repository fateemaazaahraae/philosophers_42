/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:05:53 by tiima             #+#    #+#             */
/*   Updated: 2024/06/25 20:23:59 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac != 5 && ac != 6)
        return (printf("ENTER 5 OR 6 ARGUMENTS !!\n"));
    if (check_args(av))
        return (1);
    if (init(&data, av))
        return (1);
    if (threads(&data))
        return (1);
    return (0);
}

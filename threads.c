/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:40:58 by tiima             #+#    #+#             */
/*   Updated: 2024/06/30 12:41:51 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int threads(t_data *data)
{
    int i;

    i = -1;
    data->start_time = get_current_time();
    while (++i < data->num_philo)
        if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]))
            return (clean_up(data), printf("ERROR WHILE CREATING THREADS !!\n"));
    if (data->num_philo > 1)
    {
        if (pthread_create(&data->th1, NULL, check_death, data))
            return (printf("ERROR WHILE CREATING CHECK_DEATH THREAD !!\n"));
        if (data->num_meals >= 0)
        {
            if (pthread_create(&data->th2, NULL, check_meals, data))
                return (printf("ERROR WHILE CREATING CHECK_MEALS THREAD !!\n"));
        }
        // if (check_all(data))
        //     return (1);
    }
    if (ft_join(data))
        return (1);
    return (0);
}

int ft_join(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philo)
        if (pthread_join(data->philo[i].thread, NULL))
            printf("ERROR WHILE JOINING THREADS !!\n");
    if (data->num_philo > 1)
    {
        if (pthread_join(data->th1, NULL))
            return (printf("ERROR WHILE JOINING CHECK_DEATH THREAD !!\n"));
        if (data->num_meals >= 0)
        {
            if (pthread_join(data->th2, NULL))
                return (printf("ERROR WHILE JOINING CHECK_MEALS THREAD !!\n"));
        }
    }
    return (0);
}

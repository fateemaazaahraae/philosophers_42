/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiima <tiima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:06:09 by tiima             #+#    #+#             */
/*   Updated: 2024/06/27 13:24:04 by tiima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef enum status
{
    EATING,
    SLEEPING,
    THINKING,
    DIED,
    NOTHING
}   t_status;

typedef struct philo
{
    struct s_data       *data;
    int                 id;
    int                 eat_counter;
    t_status            status;
    long long           last_eat;
    pthread_t           thread;
    pthread_mutex_t     *r_fork;
    pthread_mutex_t     *l_fork;
    pthread_mutex_t     get_lock;
    pthread_mutex_t     set_lock;
    pthread_mutex_t     lock;
    pthread_mutex_t     mtx;
    pthread_mutex_t     sleep_lock;
}                       t_philo;

typedef struct s_data
{
    t_philo             *philo;
    pthread_t           th1;
    pthread_t           th2;
    pthread_mutex_t     *forks;
    int                 num_philo;
    int                 death;
    int                 num_meals;
    long long           t_eat;
    long long           t_sleep;
    long long           t_die;
    long long           start_time;
    pthread_mutex_t     data_lock;
}                       t_data;

void    clean_all(t_data *data);

/* --parcing.c-- */
int ft_check(char *str);
int check_args(char **av);

/* --init.c-- */
int init(t_data *data, char **av);
void    init_philo(t_data *data);
int init_forks(t_data *data);
int ft_alloc(t_data *data);

/* --threads.c-- */
int threads(t_data *data);
int ft_join(t_data *data);

/* --routine.c-- */
void    *routine(void *arg);
void    message(char *str, t_philo *philo);
t_status    get_status(t_philo *philo);
void    set_status(t_philo *philo, t_status etat);

/* --actions.c-- */
int eating(t_philo *philo);
int sleeping(t_philo *philo);
int thinking(t_philo *philo);

/* --track.c-- */
void    *check_meals(void *arg);
void    *check_death(void *arg);
void    kill_all_philos(t_data *data);
int is_philo_death(t_philo *philo);

/* --utils.c-- */
int    ft_usleep(size_t milliseconds);
long long	get_current_time(void);
int	ft_atoi(char *str);


#endif
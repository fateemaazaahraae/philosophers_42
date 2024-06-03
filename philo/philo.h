/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:13:59 by fbazaz            #+#    #+#             */
/*   Updated: 2024/06/03 12:01:08 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DIED " died\n"
# define FORK " has taken a fork\n"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		th1;
	pthread_t		th2;
	int				id;
	int				eat_count;
	int				is_eating;
	u_int64_t		start;
	u_int64_t		time_die;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	message;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				n_philo;
	int				finish;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	int				n_meals;
	int				death_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	finish_lock;
}					t_data;

int					init_data(t_data *data, char **av);
void				init_philos(t_data *data);
int					init_mutex(t_data *data);
int					ft_alloc(t_data *data);
int					store_data(t_data *data, char **av);
int					ft_check(char *str);
int					check_args(char **av);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
void				message(char *str, t_philo *philo);
void				go_to_eat(t_philo *philo);
void				go_to_sleep(t_philo *philo);
void				*observer(void *arg);
void				*routine(void *arg);
int					init_threads(t_data *data);
int					ft_atoi(char *str);
u_int64_t			get_current_time(void);
int    				ft_usleep(size_t milliseconds);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:06:09 by tiima             #+#    #+#             */
/*   Updated: 2024/07/03 12:53:29 by fbazaz           ###   ########.fr       */
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
# include <limits.h>

typedef enum status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	NOTHING
}					t_status;

typedef struct philo
{
	struct s_data	*data;
	int				id;
	int				eat_counter;
	t_status		status;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			philo[201];
	pthread_t		th1;
	pthread_t		th2;
	pthread_mutex_t	forks[201];
	int				num_philo;
	int				death;
	int				num_meals;
	int				finished;
	long long		t_eat;
	long long		t_sleep;
	long long		t_die;
	long long		start_time;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	finish_lock;
}					t_data;

void				clean_up(t_data *data);

/* --parcing.c-- */
int					parcing(int ac, char **av);
int					check_digit(char *str);
int					check_sign(char *str);

/* --init.c-- */
int					init(t_data *data, char **av);
void				init_philo(t_data *data);
int					init_forks(t_data *data);
int					ft_alloc(t_data *data);

/* --threads.c-- */
int					threads(t_data *data);
int					ft_join(t_data *data);

/* --routine.c-- */
void				*routine(void *arg);
void				message(char *str, t_philo *philo);

/* --get_set.c-- */
t_status			get_status(t_philo *philo);
void				set_status(t_philo *philo, t_status etat);
void				set_value(t_data *data, int i);
int					get_value(t_data *data);

/* --actions.c-- */
int					eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);

/* --track.c-- */
void				*check_meals(void *arg);
void				*check_death(void *arg);
void				kill_all_philos(t_data *data);
int					is_philo_death(t_philo *philo);

/* --utils.c-- */
int					ft_usleep(size_t milliseconds, t_philo *philo);
long long			get_current_time(void);
long long			ft_atoi(char *str);
int					get_finish(t_data *data);
void				set_finish(t_data *data, int i);

/* --get_set2.c-- */
int	get_finish(t_data *data);
void	set_finish(t_data *data, int i);
int	get_eat(t_philo *philo);
void	set_eat(t_philo *philo);

#endif
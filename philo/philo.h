#ifndef PHILO_H
# define PHILO_H

# define PHILO_NUM 200

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define TAKE_FORK "has taken a fork\n"
# define DIE "died\n"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct philo
{
    struct data     *p;
    pthread_t       th;
    int             id;
    int             meal_counter;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
}                   t_philo;

typedef struct data
{
    t_philo         *philos;
    int             philo_num;
    u_int64_t       time_2_eat;
    u_int64_t       time_2_sleep;
    u_int64_t       time_2_die;
    int             num_of_meals;
    int             death;
    pthread_mutex_t *fork;
}                   t_data;

int	    ft_atoi(char *str);
void    ft_print_err(char *str, int i);
int     check_args(char **av);
int     init_program(t_data *p, char **av);
void    *routine(void *data);
int    init_forks(t_data *p);
void    to_eat(t_philo *philo);
void    to_sleep(t_philo *philo);
void    message(char *str, t_philo *philo);
void    take_forks(t_philo *philo);
void    drop_forks(t_philo *philo);
int     init_threads(t_data *p);

#endif
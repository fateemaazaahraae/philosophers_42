#ifndef PHILO_H
# define PHILO_H

# define PHILO_NUM 200

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct philo
{
    // t_data      *p;
    pthread_t   th;
    int         id;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
}                t_philo;

typedef struct data
{
    t_philo     *philos;
    int         philo_num;
    int         time_2_eat;
    int         time_2_sleep;
    int         time_2_die;
    int         num_of_meals;
    pthread_mutex_t *fork;
}   t_data;

int	    ft_atoi(char *str);
void    ft_print_err(char *str, int i);
int    check_args(char **av);
int    init_program(t_data *p, char **av, int ac);

#endif
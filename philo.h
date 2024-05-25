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
    int         eat;
    int         sleep;
    int         die;
    int         meals_num;
}                t_philo;

typedef struct data
{
    t_philo     *philos;
    int         philo_num;
}   t_data;

int	    ft_atoi(char *str);
void    ft_print_err(char *str, int i);
int    check_args(char **av);
void    init_program(t_data *p, char **av);

#endif
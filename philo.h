#ifndef PHILO_H
#define PHILO_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define PHILO_NUM 200

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct philo
{
    pthread_t   th;
    int         id;
    int         eat;
    int         sleep;
    int         die;
    int         meals_num;
}                t_philo;


int	    ft_atoi(char *str);
void    ft_putstr(char *str, int exit_num);
void    check_args(char **av);

#endif
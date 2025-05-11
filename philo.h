/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:54:36 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/11 15:12:50 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_main_st
{
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t is_died_mutex;
    pthread_mutex_t full_state_mutex;
    long start;
    int full_state;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philo_must_eat;
    int is_died;
} t_main_st;

typedef struct s_philo
{
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t eat_flag;
    t_main_st *main_st;
    long    last_eat_time;
    int meal_number;
    int id;
} t_philo;

int ft_is_died(t_philo  *philos);
long    ft_time(void);
int  ft_error_message(char *str);
/*parse*/
int ft_invalid_char(char *str);
int ft_check_args(char **av, t_main_st *main_st, int ac);
void    ft_fill_args(char **av, t_main_st *main_st, int ac);
/*parsing utils*/
long int	ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
/*create threads*/
void    ft_create_threads(t_main_st *main_st);
int    ft_initialize(pthread_t *philos, t_philo  *philos_prop, t_main_st *main_st);
int    ft_init_forks(t_main_st *main_st);
void    ft_philo_init(t_philo *ph_prop, t_main_st *main_st);
void    ft_init_last_eat(t_philo *philos);
/*threads logic*/
void    *monitor_thread(void *arg);
void    *philo_thread(void  *arg);
void    ft_sleep(t_philo *philo, long time);
/*threads logic utils*/
void    ft_one_philo(t_philo *philo);
int    ft_sleeping(t_philo *philo);
int    ft_eating(t_philo *philo);
int    ft_thinking(t_philo *philo);
void    ft_free(pthread_t *philos, t_philo *philos_prop);
void   ft_print(t_philo *philo, char *message);
#endif
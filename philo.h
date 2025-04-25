/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:54:36 by isakrout          #+#    #+#             */
/*   Updated: 2025/04/25 08:14:14 by isakrout         ###   ########.fr       */
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
    long start;
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
    pthread_mutex_t last_eat_time_mutex;
    pthread_mutex_t meal_number_mutex;
    t_main_st *main_st;
    long    last_eat_time;
    int meal_number;
    int id;
} t_philo;
/*args*/
char    *ft_join_args(char **av);
int ft_invalid_char(char *str);
int ft_check_split(char **args);
int ft_check_args(char **av, t_main_st *main_st, int ac);
void    ft_fill_args(char **av, t_main_st *main_st, int ac);
/*utils*/
int ft_error_message(char *str);
int ft_strlen(char const *str);
/*parsing utils*/
long int	ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void    ft_free_split(char **av);
/*strjoin*/
void	ft_join(char *str, char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
/*ft_split*/
char	**ft_split(char const *s, char c);
/**/
int ft_is_died(t_philo  *philos);
#endif
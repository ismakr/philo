/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:54:41 by isakrout          #+#    #+#             */
/*   Updated: 2025/04/18 11:16:40 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char const *str)
{
    int i;

    i = 0;
    while (*str)
    {
        str++;
        i++;
    }
    return (i);
}

int ft_error_message(char *str)
{
    write(2, "Error\n", 6);
    write(2, str, ft_strlen(str));
    return(1);
}

long    ft_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    ft_thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->main_st->print);
    printf("%ld %d is thinking\n",ft_time() - philo->main_st->start, philo->id);
    pthread_mutex_unlock(&philo->main_st->print);
}

void    *philo_thread(void  *arg)
{
    t_philo  *philo;

    philo = (t_philo*)arg;
   // while (1)
    //{
        ft_thinking(philo);
        // ft_eating(prop);
        // ft_sleeping(prop);
    //}
    return (NULL);
}

void    ft_philo_init(t_philo *ph_prop, t_main_st *main_st)
{
    int i;
    int n;

    i = 0;
    n = 1;
    while (i < main_st->number_of_philosophers)
    {
        (ph_prop + i)->id = n;
        (ph_prop + i)->main_st = main_st;
        i++;
        n++;
    }
}

void    ft_init_forks(t_main_st *main_st)
{
    int i;
    main_st->forks = ft_calloc(main_st->number_of_philosophers, sizeof(pthread_mutex_t));
    i = 0;
    while (i < main_st->number_of_philosophers)
    {
        pthread_mutex_init(&main_st->forks[i], NULL);
        i++;
    }
}

void    ft_create_threads(t_main_st *main_st)
{
    pthread_t *philos;
    t_philo  *philos_prop;
    int i;

    philos = ft_calloc(main_st->number_of_philosophers, sizeof(pthread_t));
    philos_prop = ft_calloc(main_st->number_of_philosophers, sizeof(t_philo));
    ft_init_forks(main_st);
    ft_philo_init(philos_prop, main_st);
    //pthread_mutex_init(&var_str.mymutex, NULL);
    main_st->start = ft_time();
    i = 0;
    while (i < main_st->number_of_philosophers)
    {
        pthread_create(&philos[i], NULL, philo_thread, &philos_prop[i]);
        i++;
    }
    i = 0;
    while (i < main_st->number_of_philosophers)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
    free(philos);
    //pthread_mutex_destroy(&var_str.mymutex);
}

int main(int ac, char **av)
{
    t_main_st  *main_st;

    main_st = ft_calloc(1, sizeof(t_main_st));
    if (ft_check_args(av, main_st, ac) == -1)
        return (free(main_st), ft_error_message("invalid args\n"));
    ft_create_threads(main_st);
    free(main_st);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:54:41 by isakrout          #+#    #+#             */
/*   Updated: 2025/04/25 09:02:12 by isakrout         ###   ########.fr       */
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

int  ft_error_message(char *str)
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

void    ft_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->main_st->print);
    if (philo->main_st->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n",ft_time() - philo->main_st->start, philo->id);
        usleep(philo->main_st->time_to_die);
        pthread_mutex_unlock(philo->l_fork);
        return ;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork\n",ft_time() - philo->main_st->start, philo->id);
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n",ft_time() - philo->main_st->start, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n",ft_time() - philo->main_st->start, philo->id);
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork\n",ft_time() - philo->main_st->start, philo->id);
    }
    printf("%ld %d is eating\n",ft_time() - philo->main_st->start, philo->id);
    pthread_mutex_unlock(&philo->main_st->print);
    /*last_eat_time lock: cuz the monitor will read it*/
    pthread_mutex_lock(&philo->last_eat_time_mutex);
    philo->last_eat_time = ft_time();
    pthread_mutex_unlock(&philo->last_eat_time_mutex);
    usleep(philo->main_st->time_to_eat * 1000);
    /*meal number lock: cuz the monitor will read it*/
    pthread_mutex_lock(&philo->meal_number_mutex);
    philo->meal_number += 1;
    pthread_mutex_unlock(&philo->meal_number_mutex);
    /*****************/
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void    ft_sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->main_st->print);
    printf("%ld %d is sleeping\n",ft_time() - philo->main_st->start, philo->id);
    pthread_mutex_unlock(&philo->main_st->print);
    // pthread_mutex_lock(&philo->main_st->tt_sleep);
    usleep(philo->main_st->time_to_sleep * 1000);
}
/*
each thread will read and write the value of
number_of_times_each_philo_must_eat
meal_number
last_eat_time
time_to_die
they should be all protected by mutex
*/
void    *philo_thread(void  *arg)
{
    t_philo  *philo;

    philo = (t_philo*)arg;
    while (!ft_is_died(philo))
    {
        ft_thinking(philo);
        ft_eating(philo);
        ft_sleeping(philo);
    }
    return (NULL);
}

int ft_is_died(t_philo  *philos)
{
    int died;

    pthread_mutex_lock(&philos->main_st->is_died_mutex);
    died = philos->main_st->is_died;
    pthread_mutex_unlock(&philos->main_st->is_died_mutex);
    return (died);
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
        (ph_prop + i)->r_fork = &main_st->forks[i];
        (ph_prop + i)->l_fork = &main_st->forks[(i + 1) % main_st->number_of_philosophers];
        pthread_mutex_init(&(ph_prop + i)->last_eat_time_mutex, NULL);
        pthread_mutex_init(&(ph_prop + i)->last_eat_time_mutex, NULL);
        i++;
        n++;
    }
}

int    ft_init_forks(t_main_st *main_st)
{
    int i;

    main_st->forks = ft_calloc(main_st->number_of_philosophers, sizeof(pthread_mutex_t));
    if (main_st->forks == NULL)
        return (-1);
    i = 0;
    while (i < main_st->number_of_philosophers)
    {
        pthread_mutex_init(&main_st->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&main_st->print, NULL);
    pthread_mutex_init(&main_st->is_died_mutex, NULL);
    return (0);
}

void    *monitor_thread(void *arg)
{
    t_philo *philos;
    int i;

    philos = (t_philo *)arg;
    while (1)
    {
        i = 0;
        while (i < philos->main_st->number_of_philosophers)
        {
            pthread_mutex_lock(&(philos + i)->last_eat_time_mutex);
            if (ft_time() - (philos + i)->last_eat_time > (philos + i)->main_st->time_to_die)
            {
                pthread_mutex_lock(&(philos + i)->main_st->is_died_mutex);
                philos->main_st->is_died = 1;
                pthread_mutex_unlock(&(philos + i)->main_st->is_died_mutex);
                pthread_mutex_lock(&philos->main_st->print);
                printf("%ld %d is died\n",ft_time() - (philos + i)->main_st->start, (philos + i)->id);
                pthread_mutex_unlock(&philos->main_st->print);
                pthread_mutex_unlock(&(philos + i)->last_eat_time_mutex);
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
}

void    ft_create_threads(t_main_st *main_st)
{
    pthread_t *philos;
    pthread_t monitor;
    t_philo  *philos_prop;
    int i;

    //allocate and init the philos and its properties
    philos = ft_calloc(main_st->number_of_philosophers, sizeof(pthread_t));
    philos_prop = ft_calloc(main_st->number_of_philosophers, sizeof(t_philo));
    if (philos == NULL || philos_prop == NULL)
        return (free(philos), free(philos_prop));
    if (ft_init_forks(main_st) == -1)
        return (free(philos), free(philos_prop));
    ft_philo_init(philos_prop, main_st);
    //create threads and start simulation
    main_st->start = ft_time();
    pthread_create(&monitor, NULL, monitor_thread, philos_prop);
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
    pthread_join(monitor, NULL);
    //free(philos);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:36:09 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/11 09:38:47 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_eat_number_check(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->main_st->number_of_philosophers)
    {
        if ((philos+i)->meal_number < philos->main_st->number_of_philosophers)
            break;
        i++;
    }
    if(i == philos->main_st->number_of_philosophers)
    {
        pthread_mutex_lock(&philos->main_st->is_died_mutex);
        philos->main_st->is_died = 1;
        pthread_mutex_unlock(&philos->main_st->is_died_mutex);
        return (1);
    }
    return (0);
}

int    monitor_utils(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->main_st->number_of_philosophers)
    {
        pthread_mutex_lock(&philos[i].eat_flag);
        if (ft_time() - philos[i].last_eat_time >= philos[i].main_st->time_to_die)
        {
            pthread_mutex_lock(&philos->main_st->print);
            printf("%ld %d %s\n", ft_time() - philos->main_st->start, philos[i].id, "is died");
            pthread_mutex_unlock(&philos->main_st->print);
            pthread_mutex_lock(&philos->main_st->is_died_mutex);
            philos->main_st->is_died = 1;
            pthread_mutex_unlock(&philos->main_st->is_died_mutex);
            pthread_mutex_unlock(&philos[i].eat_flag);
            return (1);
        }
        pthread_mutex_unlock(&philos[i].eat_flag);
        i++;
    }
    return (0);
}



void    *monitor_thread(void *arg)
{
    t_philo *philos;
    int i;
    philos = (t_philo *)arg;
    if (philos->main_st->number_of_times_each_philo_must_eat == 0)
        return (NULL);
    while (1)
    {
        i = 0;
        if (monitor_utils(philos) == 1)
            return (NULL);
        pthread_mutex_lock(&philos->main_st->full_state_mutex);
        if (philos->main_st->number_of_times_each_philo_must_eat != -1 && philos->main_st->full_state == philos->main_st->number_of_philosophers)
        {
            pthread_mutex_unlock(&philos->main_st->full_state_mutex);
            pthread_mutex_lock(&philos->main_st->is_died_mutex);
            philos->main_st->is_died = 1;
            pthread_mutex_unlock(&philos->main_st->is_died_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&philos->main_st->full_state_mutex);
       usleep(1000);
    }
}

void    *philo_thread(void  *arg)
{
    t_philo  *philo;

    philo = (t_philo*)arg;
    if (philo->main_st->number_of_times_each_philo_must_eat == 0)
        return (NULL);
    while (ft_is_died(philo) != 1)
    {
        if (ft_thinking(philo) == 1)
            break;
        if (ft_eating(philo) == 1)
            break;
        if (ft_sleeping(philo) == 1)
            break;
    }
    return (NULL);
}
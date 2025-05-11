/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_logic_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:38:16 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/11 15:39:49 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_thinking(t_philo *philo)
{
    if (ft_is_died(philo) == 1)
        return (1);
    ft_print(philo, "is thinking");
    return (0);
}

void   ft_print(t_philo *philo, char *message)
{
    if (ft_is_died(philo) == 1)
        return;
    pthread_mutex_lock(&philo->main_st->is_died_mutex);
    if (philo->main_st->is_died != 1)
    {
        pthread_mutex_lock(&philo->main_st->print);
        printf("%ld %d %s\n", ft_time() - philo->main_st->start, philo->id, message);
        pthread_mutex_unlock(&philo->main_st->print);
    }
    pthread_mutex_unlock(&philo->main_st->is_died_mutex);
}

int ft_take_forks(t_philo *philo)
{
    if (ft_is_died(philo) == 1)
        return (1);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        ft_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        ft_print(philo, "has taken a fork");
    }
    else
    {
        usleep(1000);
        pthread_mutex_lock(philo->l_fork);
        ft_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        ft_print(philo, "has taken a fork");
    }
    philo->last_eat_time = ft_time();
    return (0);
}

void    ft_one_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    ft_print(philo, "has taken a fork");
    usleep(philo->main_st->time_to_die * 1000);
    pthread_mutex_unlock(philo->l_fork);
}

int    ft_eating_utils(t_philo *philo)
{
    if (ft_is_died(philo) == 1)
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return (1);
    }
    pthread_mutex_lock(&philo->eat_flag);
    philo->last_eat_time = ft_time();
    philo->meal_number += 1;
    pthread_mutex_unlock(&philo->eat_flag);
    if (philo->main_st->number_of_times_each_philo_must_eat != -1)
    {
        pthread_mutex_lock(&philo->main_st->full_state_mutex);
        if (philo->meal_number >= philo->main_st->number_of_times_each_philo_must_eat)
            philo->main_st->full_state++;
        //printf("========================%d\n" ,   philo->main_st->full_state);
        pthread_mutex_unlock(&philo->main_st->full_state_mutex);
    }
    ft_print(philo, "is eating");
    usleep(philo->main_st->time_to_eat * 1000);
    return (0);
}

int    ft_eating(t_philo *philo)
{
    if (ft_is_died(philo) == 1)
        return (1);
    if (ft_take_forks(philo) == 1)
        return (1);
    if (ft_eating_utils(philo) == 1)
        return (1);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    return (0);
}

// void    ft_sleep(t_philo *philo, long time)
// {
//     int start;
//     start = ft_time();
//     while ((ft_time() - start) * 1000 < time)
//     {
//         pthread_mutex_lock(&philo->main_st->is_died_mutex);
//         if (philo->main_st->is_died == 1)
//         {
//             pthread_mutex_unlock(&philo->main_st->is_died_mutex);
//             break ;
//         }
//         pthread_mutex_unlock(&philo->main_st->is_died_mutex);
//         usleep(100);
//     }
// }

int    ft_sleeping(t_philo *philo)
{
    if (ft_is_died(philo) == 1)
        return (1);
    ft_print(philo, "is sleeping");
    usleep(philo->main_st->time_to_sleep * 1000);
    return (0);
}

void    ft_free(pthread_t *philos, t_philo *philos_prop)
{
    int i;

    i = 0;
    while (i < philos_prop->main_st->number_of_philosophers)
    {
        pthread_mutex_destroy(&philos_prop->main_st->forks[i]);
        pthread_mutex_destroy(&philos_prop[i].eat_flag);
        i++;
    }
    pthread_mutex_destroy(&philos_prop->main_st->print);
    pthread_mutex_destroy(&philos_prop->main_st->is_died_mutex);
    pthread_mutex_destroy(&philos_prop->main_st->full_state_mutex);
    free(philos);
}

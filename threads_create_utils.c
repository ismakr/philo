/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_create_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:22:34 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/14 10:39:58 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    free(philos_prop->main_st->forks);
    free(philos);
    free(philos_prop);
}

void    ft_create_threads_utils(t_philo *philos_prop, pthread_t *philos)
{
    int i;
    i = 0;
    while (i < philos_prop->main_st->number_of_philosophers)
    {
        philos_prop[i].last_eat_time = ft_time();
        pthread_create(&philos[i], NULL, philo_thread, &philos_prop[i]);
        i++;
    }
}

void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, "has taken a fork");
	usleep(philo->main_st->time_to_die * 1000);
	pthread_mutex_unlock(philo->l_fork);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:07:27 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/14 10:29:26 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
        pthread_mutex_init(&ph_prop[i].eat_flag, NULL);
        i++;
        n++;
    }
}

int ft_init_forks(t_main_st *main_st)
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
    pthread_mutex_init(&main_st->full_state_mutex, NULL);
    return (0);
}

int ft_initialize(pthread_t *philos, t_philo  *philos_prop, t_main_st *main_st)
{
    if (ft_init_forks(main_st) == -1)
        return (free(philos), free(philos_prop), -1);
    ft_philo_init(philos_prop, main_st);
    return (0);
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
    if (ft_initialize(philos, philos_prop, main_st) == -1)
        return ;
    //create threads and start simulation
    main_st->start = ft_time();
    ft_create_threads_utils(philos_prop, philos);
    i = 0;
    pthread_create(&monitor, NULL, monitor_thread, philos_prop);
    while (i < main_st->number_of_philosophers)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
    pthread_join(monitor, NULL);
    ft_free(philos, philos_prop);
}

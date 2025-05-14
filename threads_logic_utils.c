/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_logic_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:38:16 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/14 10:39:49 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_thinking(t_philo *philo)
{
	if (ft_is_died(philo) == 1)
		return (1);
	ft_print(philo, "is thinking");
	return (0);
}

int	ft_take_forks(t_philo *philo)
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
	pthread_mutex_lock(&philo->eat_flag);
	philo->last_eat_time = ft_time();
	pthread_mutex_unlock(&philo->eat_flag);
	return (0);
}

int	ft_eating_utils(t_philo *philo)
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
		pthread_mutex_lock(&philo->eat_flag);
		if (philo->meal_number
			>= philo->main_st->number_of_times_each_philo_must_eat)
			philo->main_st->full_state++;
		pthread_mutex_unlock(&philo->eat_flag);
		pthread_mutex_unlock(&philo->main_st->full_state_mutex);
	}
	ft_print(philo, "is eating");
	usleep(philo->main_st->time_to_eat * 1000);
	return (0);
}

int	ft_eating(t_philo *philo)
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

int	ft_sleeping(t_philo *philo)
{
	if (ft_is_died(philo) == 1)
		return (1);
	ft_print(philo, "is sleeping");
	usleep(philo->main_st->time_to_sleep * 1000);
	return (0);
}

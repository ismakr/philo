/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:54:41 by isakrout          #+#    #+#             */
/*   Updated: 2025/05/21 20:51:40 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

int	ft_error_message(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	return (1);
}

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_is_died(t_philo *philos)
{
	pthread_mutex_lock(&philos->main_st->is_died_mutex);
	if (philos->main_st->is_died == 1)
	{
		pthread_mutex_unlock(&philos->main_st->is_died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->main_st->is_died_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	t_main_st	*main_st;

	if (ac != 5 && ac != 6)
		return (1);
	main_st = ft_calloc(1, sizeof(t_main_st));
	if (ft_check_args(av, main_st, ac) == -1)
		return (free(main_st), ft_error_message("invalid args\n"));
	ft_create_threads(main_st);
	free(main_st);
}

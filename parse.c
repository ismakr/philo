/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:25:44 by isakrout          #+#    #+#             */
/*   Updated: 2025/04/28 23:21:33 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_invalid_char(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '-' || str[i] == '+')
            i++;
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (-1);
        i++;  
    }
    return (0);
}

int ft_check_args(char **av, t_main_st *main_st, int ac)
{
    int i;

    i = 1;
    while (av[i])
    {
        if (ft_invalid_char(av[i]) == -1)
            return (-1);
        if (ft_atoi(av[i]) < 0 || ft_atoi(av[1]) == 0)
            return (-1);
        i++;
    }
    ft_fill_args(av, main_st, ac);
    return (0);
}

void    ft_fill_args(char **av, t_main_st *main_st, int ac)
{
    main_st->number_of_philosophers = ft_atoi(av[1]);
    main_st->time_to_die = ft_atoi(av[2]);
    main_st->time_to_eat = ft_atoi(av[3]);
    main_st->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        main_st->number_of_times_each_philo_must_eat = ft_atoi(av[5]);
    else
        main_st->number_of_times_each_philo_must_eat = -1;
}
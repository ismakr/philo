/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:25:44 by isakrout          #+#    #+#             */
/*   Updated: 2025/04/18 10:22:17 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char    *ft_join_args(char **av)
{
    char    *finale_str;
    char    *ptr_free;
    int i;
    i = 1;
    finale_str = ft_strdup("");
    while (av[i])
    {
        ptr_free = finale_str;
        finale_str = ft_strjoin(finale_str, av[i]);
        free(ptr_free);
        i++;
    }
    return (finale_str);
}

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

int ft_check_split(char **args)
{
    int i;
    int c;

    i = 0;
    c = 0;
    while (args[i])
    {
        c = ft_invalid_char(args[i]);
        if (c == -1)
            return (-1);
        if (ft_atoi(args[i]) < 0)
            return (-1);
        i++;
    }
    if (i != 4 && i != 5)
        return (-1);
    return (c);
}

int ft_check_args(char **av, t_main_st *main_st, int ac)
{
    int c;
    char    *joined_args;
    char    **splited_args;

    c = 0;
    joined_args = ft_join_args(av);
    splited_args = ft_split(joined_args, ' ');
    c = ft_check_split(splited_args);
    if (c == -1)
    {
        free(joined_args);
        ft_free_split(splited_args);
        return (-1);
    }
    ft_fill_args(splited_args, main_st, ac);
    free(joined_args);
    ft_free_split(splited_args);
    return (c);
}

void    ft_fill_args(char **av, t_main_st *main_st, int ac)
{
    main_st->number_of_philosophers = ft_atoi(av[0]);
    main_st->time_to_die = ft_atoi(av[1]);
    main_st->time_to_eat = ft_atoi(av[2]);
    main_st->time_to_sleep = ft_atoi(av[3]);
    if (ac == 6)
        main_st->number_of_times_each_philo_must_eat = ft_atoi(av[4]);
}
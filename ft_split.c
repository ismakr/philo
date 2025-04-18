/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isakrout <isakrout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:15:25 by isakrout          #+#    #+#             */
/*   Updated: 2025/04/13 15:39:55 by isakrout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	j;
	int	res;

	res = 0;
	i = 0;
	j = ft_strlen(s) - 1;
	if (j < 0)
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (j != 0 && s[j] == c)
		j--;
	while (s[i] && i <= j)
	{
		if (s[i] == c && s[i - 1] != c)
			res += 1;
		i++;
	}
	if (res == 0 && s[i - 1] == c)
		return (res);
	res += 1;
	return (res);
}

static void	ft_fill(char *p, char const *s, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
}

static void	ft_free(char *arr, int j)
{
	j--;
	while (j >= 0)
	{
		free(&arr[j]);
		j--;
	}
	free(arr);
}

static int	ft_allo(char **arr, int i, char const *s, char c)
{
	int	wc;
	int	l;

	l = i;
	wc = 0;
	while (s[l] != c && s[l])
	{
		wc++;
		l++;
	}
	*arr = malloc(wc * sizeof(char) + 1);
	if (arr == NULL)
	{
		return (0);
	}
	ft_fill(*arr, &s[i], wc);
	if (!s[l] && l != 1)
		l--;
	return (l);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;
	int		j;

	j = 0;
	arr = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < ft_strlen(s))
	{
		if (s[i] != c && s[i])
		{
			i = ft_allo(&arr[j], i, s, c);
			if (i == 0)
			{
				ft_free(arr[j], j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

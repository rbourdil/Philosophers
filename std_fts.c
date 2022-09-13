/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:44:04 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/13 14:16:54 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != 0 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(*s1 - *s2));
}

void	ft_memset(void *s, int c, size_t n)
{
	while (n-- > 0)
		*(char *)s++ = c;
}

int	ft_atoi(char *s)
{
	int	n;
	int	sign;

	while (*s == ' ')
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	n = 0;
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0') * sign;
		s++;
	}
	return (n);
}

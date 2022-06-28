/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:38:44 by rbourdil          #+#    #+#             */
/*   Updated: 2022/06/23 15:31:19 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now(void)
{
	static long		start = -1;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (start == -1)
		start = (long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000;
	return ((long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000 - start);
}

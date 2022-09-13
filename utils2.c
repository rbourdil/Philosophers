/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:45:50 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/13 14:38:30 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	done_eating(t_params *params)
{
	pthread_mutex_lock(&params->nb_done_eating_mutex);
	params->nb_done_eating++;
	pthread_mutex_unlock(&params->nb_done_eating_mutex);
}

int	everyone_done_eating(t_params *params)
{
	pthread_mutex_lock(&params->nb_done_eating_mutex);
	if (params->nb_done_eating == params->eat_count)
	{
		pthread_mutex_unlock(&params->nb_done_eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(&params->nb_done_eating_mutex);
	return (0);
}

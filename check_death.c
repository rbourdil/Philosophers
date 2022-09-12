/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:27:29 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 17:27:30 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_simul(t_params *params)
{
	pthread_mutex_lock(&params->death_mutex);
	params->death = 1;
	pthread_mutex_unlock(&params->death_mutex);
}

void	*check_death(void *arg)
{
	t_params	*params;
	int			i;

	params = (t_params *)arg;
	while (!everyone_done_eating(params))
	{
		i = 0;
		while (i < params->nb_philos)
		{
			if (isdead(params, i))
			{
				printf("%d %d died\n", now() - params->start, i + 1);
				return (NULL);
			}
			i++;
		}
		usleep(MICRO_PAUSE);
	}
	end_simul(params);
	return (NULL);
}

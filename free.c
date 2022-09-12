/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:29:01 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 17:29:03 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_params(t_params *params)
{
	free(params->time_of_death_mutexes);
	free(params->time_of_death);
	free(params->forks);
}

void	destroy_mutexes(t_params *params)
{
	int	i;

	pthread_mutex_destroy(&params->death_mutex);
	pthread_mutex_destroy(&params->nb_done_eating_mutex);
	i = 0;
	while (i < params->nb_philos)
	{
		pthread_mutex_destroy(&params->time_of_death_mutexes[i]);
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
}

void	join_threads(pthread_t *threads, int n)
{
	while (--n >= 0)
		pthread_join(threads[n], NULL);
}

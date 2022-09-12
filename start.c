/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:29:49 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 17:43:42 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_free(int i, pthread_t *threads, t_philo *philo)
{
	join_threads(threads, i);
	free(threads);
	free(philo);
}

static void	launch(int i, t_params *params, pthread_t *threads, t_philo *philo)
{
	int	status;

	philo->id = i;
	philo->params = params;
	params->time_of_death[i] = params->start + params->time_to_die;
	if (params->nb_philos == 1)
		status = pthread_create(&threads[i], NULL, solo_philo, philo);
	else
		status = pthread_create(&threads[i], NULL, eat_sleep_think, philo);
	if (status != 0)
	{
		join_free(i, threads, philo);
		free_print_exit("thread creation failed", params);
	}
}

void	start_philo_threads(pthread_t *threads, t_params *params)
{
	t_philo		*philo;
	int			i;

	params->start = now();
	i = 0;
	while (i < params->nb_philos)
	{
		philo = malloc(sizeof(t_philo));
		if (philo == NULL)
		{
			join_free(i, threads, philo);
			free_print_exit("memory allocation failed", params);
		}
		launch(i, params, threads, philo);
		i++;
	}
}

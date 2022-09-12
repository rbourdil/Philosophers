/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:27:40 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 18:07:35 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_forks(t_params *params, int id)
{
	if (id % 2 == 0)
		pthread_mutex_lock(&params->forks[id]);
	else
		pthread_mutex_lock(&params->forks[(id + 1) % params->nb_philos]);
	print_action(id, params, FORK);
	if (id % 2 == 0)
		pthread_mutex_lock(&params->forks[(id + 1) % params->nb_philos]);
	else
		pthread_mutex_lock(&params->forks[id]);
	print_action(id, params, FORK);
}

static void	release_forks(t_params *params, int id)
{
	pthread_mutex_unlock(&params->forks[id]);
	pthread_mutex_unlock(&params->forks[(id + 1) % params->nb_philos]);
}

static void	eat(t_params *params, int id)
{
	grab_forks(params, id);
	pthread_mutex_lock(&params->time_of_death_mutexes[id]);
	params->time_of_death[id] = now() + params->time_to_die;
	pthread_mutex_unlock(&params->time_of_death_mutexes[id]);
	print_action(id, params, EAT);
	usleep(params->time_to_eat * 1000);
	release_forks(params, id);
}

static int	update_eat_count(int eat_count, t_params *params)
{
	if (eat_count > 0)
		eat_count--;
	if (eat_count == 0)
	{
		eat_count = -1;
		done_eating(params);
	}
	return (eat_count);
}

void	*eat_sleep_think(void *arg)
{
	t_philo	*philo;
	int		eat_count;

	philo = (t_philo *)arg;
	eat_count = philo->params->eat_count;
	if (eat_count == 0)
	{
		done_eating(philo->params);
		free(arg);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(PAUSE);
	while (!someone_died(philo->params) && !everyone_done_eating(philo->params))
	{
		eat(philo->params, philo->id);
		eat_count = update_eat_count(eat_count, philo->params);
		print_action(philo->id, philo->params, SLEEP);
		usleep(philo->params->time_to_sleep * 1000);
		print_action(philo->id, philo->params, THINK);
		usleep(PAUSE);
	}
	free(arg);
	return (NULL);
}

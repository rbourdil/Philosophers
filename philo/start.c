/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:35:17 by rbourdil          #+#    #+#             */
/*   Updated: 2022/06/28 11:32:54 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pause_exec(t_params *params, unsigned int pause_len)
{
	long	time_left;

	time_left = params->death_date - now();
	if (pause_len < time_left)
	{
		usleep(pause_len * 1000);
		return (0);
	}
	else
	{
		if (time_left >= 0)
			usleep(pause_len * 1000);
		return (1);
	}
}

void	release_forks(t_params *params, int opt)
{
	if ((opt & FIRST) != 0)
		pthread_mutex_unlock(params->first);
	if ((opt & SECOND) != 0)
		pthread_mutex_unlock(params->second);
}

int	print_action(t_params *params, int action)
{
	int	status;

	status = ALIVE;
	pthread_mutex_lock(&params->common->dead_mutex);
	if (params->common->dead == DEAD)
		status = DEAD;
	else if (params->death_date < now())
	{
		printf("%ld %d died\n", now(), params->philo_id);
		params->common->dead = DEAD;
		status = DEAD;
	}
	else if ((action & FORK) != 0)
		printf("%ld %d has taken a fork\n", now(), params->philo_id);
	else if ((action & EAT) != 0)
		printf("%ld %d is eating\n", now(), params->philo_id);
	else if ((action & SLEEP) != 0)
		printf("%ld %d is sleeping\n", now(), params->philo_id);
	else if ((action & THINK) != 0)
		printf("%ld %d is thinking\n", now(), params->philo_id);
	pthread_mutex_unlock(&params->common->dead_mutex);
	return (status);
}

static int	eat(t_params *params)
{
	pthread_mutex_lock(params->first);
	if (print_action(params, FORK) == DEAD)
	{
		release_forks(params, FIRST);
		return (DEAD);
	}
	pthread_mutex_lock(params->second);
	if (print_action(params, FORK) == DEAD)
	{
		release_forks(params, FIRST | SECOND);
		return (DEAD);
	}
	if (print_action(params, EAT) == DEAD)
	{
		release_forks(params, FIRST | SECOND);
		return (DEAD);
	}
	params->death_date = now() + params->time_to_die;
	pause_exec(params, params->time_to_eat);
	release_forks(params, FIRST | SECOND);
	return (ALIVE);
}

void	*eat_sleep_think(void *args)
{
	t_params	*params;

	params = (t_params *)args;
	while (print_action(params, 0) == ALIVE)
	{
		if (params->eat_count == 0)
			break ;
		if (eat(params) == DEAD)
			break ;
		params->eat_count--;
		if (print_action(params, SLEEP) == DEAD)
			break ;
		pause_exec(params, params->time_to_sleep);
		if (print_action(params, THINK) == DEAD)
			break ;
		if (usleep(PAUSE) == -1)
		{
			perror("usleep");
			exit(EXIT_FAILURE);
		}
	}
	return (params);
}

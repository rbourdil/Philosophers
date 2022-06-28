/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:34:51 by rbourdil          #+#    #+#             */
/*   Updated: 2022/06/28 11:35:37 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(int nb_philos)
{
	pthread_mutex_t	*forks;
	int				status;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < nb_philos)
	{
		status = pthread_mutex_init(&forks[i], NULL);
		if (status != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static t_common	*init_common(void)
{
	t_common	*common;

	common = (t_common *)malloc(sizeof(t_common));
	if (common == NULL)
		return (NULL);
	pthread_mutex_init(&common->dead_mutex, NULL);
	common->dead = ALIVE;
	return (common);
}

static t_params	*init_params(int i, pthread_mutex_t *forks, \
t_common *common, char *argv[])
{
	t_params	*params;

	params = (t_params *)malloc(sizeof(t_params));
	if (params == NULL)
		return (NULL);
	params->philo_id = i + 1;
	if (params->philo_id % 2 == 1)
	{
		params->first = &forks[(atoi(argv[1]) + i - 1) % atoi(argv[1])];
		params->second = &forks[i];
	}
	else
	{
		params->first = &forks[i];
		params->second = &forks[(atoi(argv[1]) + i - 1) % atoi(argv[1])];
	}
	params->common = common;
	params->time_to_die = atoi(argv[2]);
	params->time_to_eat = atoi(argv[3]);
	params->time_to_sleep = atoi(argv[4]);
	params->eat_count = -1;
	if (argv[5] != NULL)
		params->eat_count = atoi(argv[5]);
	params->death_date = now() + params->time_to_die;
	return (params);
}

static int	start_philo(int i, pthread_t *philos, t_params *params, int nb_philos)
{
	int			status;

	if (nb_philos > 1)
		status = pthread_create(&philos[i], NULL, eat_sleep_think, params);
	else
		status = pthread_create(&philos[i], NULL, alone, params);
	if (status != 0)
	{
		free(params);
		join_philos(philos, i);
		return (-1);
	}
	return (0);
}

pthread_t	*init_philos(char *argv[], pthread_mutex_t *forks, int nb_philos)
{
	pthread_t	*philos;
	t_params	*params;
	t_common	*common;
	int			i;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * nb_philos);
	if (philos == NULL)
		return (NULL);
	common = init_common();
	if (common == NULL)
		return (NULL);
	i = 0;
	while (i < nb_philos)
	{
		params = init_params(i, forks, common, argv);
		if (params == NULL)
		{
			join_philos(philos, i);
			return (NULL);
		}
		if (start_philo(i, philos, params, nb_philos) == -1)
			return (NULL);
		i++;
	}
	return (philos);
}

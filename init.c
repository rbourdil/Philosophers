/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:29:15 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/13 14:05:34 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_command_line_params(t_params *params, int argc, char *argv[])
{
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		params->eat_count = ft_atoi(argv[5]);
	else
		params->eat_count = -1;
}

static void	allocate_mem(t_params *params, int nb_philos)
{
	params->time_of_death_mutexes = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (params->time_of_death_mutexes == NULL)
		print_exit("memory allocation failed\n");
	params->time_of_death = malloc(sizeof(int) * nb_philos);
	if (params->time_of_death == NULL)
	{
		free_params(params);
		print_exit("memory allocation failed\n");
	}
	params->forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (params->forks == NULL)
	{
		free_params(params);
		print_exit("memory allocation failed\n");
	}
}

static void	init_mutexes(t_params *params, int nb_philos)
{
	int	i;
	int	status;

	status = 0;
	status += pthread_mutex_init(&params->death_mutex, NULL);
	status += pthread_mutex_init(&params->nb_done_eating_mutex, NULL);
	i = 0;
	while (i < nb_philos)
	{
		status += pthread_mutex_init(&params->time_of_death_mutexes[i], NULL);
		status += pthread_mutex_init(&params->forks[i], NULL);
		i++;
	}
	if (status != 0)
	{
		destroy_mutexes(params);
		free_params(params);
		print_exit("mutex init failed");
	}
}	

void	init_params(t_params *params, int argc, char *argv[])
{
	int	nb_philos;

	nb_philos = ft_atoi(argv[1]);
	params->nb_philos = nb_philos;
	params->death = 0;
	params->nb_done_eating = 0;
	init_command_line_params(params, argc, argv);
	allocate_mem(params, nb_philos);
	init_mutexes(params, nb_philos);
}

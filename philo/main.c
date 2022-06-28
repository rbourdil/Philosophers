/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:50:26 by rbourdil          #+#    #+#             */
/*   Updated: 2022/06/23 18:01:34 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philos(pthread_t *philos, int nb_philos)
{
	t_params	*params;
	int			i;

	i = 0;
	while (i < nb_philos - 1)
	{
		pthread_join(philos[i++], (void **)&params);
		free(params);
	}
	pthread_join(philos[i], (void **)&params);
	free(params->common);
	free(params);
}

static void	destroy_forks(pthread_mutex_t *forks, int nb_forks)
{
	int	i;

	i = 0;
	while (i < nb_forks)
		pthread_mutex_destroy(&forks[i++]);
}

int	main(int argc, char *argv[])
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6)
		err_abort("usage: ./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	if (check_args(argc, argv) == -1)
		err_abort("Invalid arguments\n");
	forks = init_forks(atoi(argv[1]));
	if (forks == NULL)
		err_abort("Mutex initialization failed\n");
	philos = init_philos(argv, forks, atoi(argv[1]));
	if (philos == NULL)
		err_abort("Threads creation failed\n");
	join_philos(philos, atoi(argv[1]));
	destroy_forks(forks, atoi(argv[1]));
	free(philos);
	free(forks);
	return (0);
}

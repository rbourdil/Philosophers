/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:29:25 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/13 14:11:11 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_params	params;
	pthread_t	*philo_threads;
	pthread_t	checker;

	if (argc < 5 || argc > 6)
	{
		printf("invalid number of arguments\n");
		input_err_exit();
	}
	check_args(argc, argv);
	ft_memset(&params, '\0', sizeof(t_params));
	init_params(&params, argc, argv);
	philo_threads = malloc(sizeof(pthread_t) * params.nb_philos);
	if (philo_threads == NULL)
		free_print_exit("memory allocation failed", &params);
	start_philo_threads(philo_threads, &params);
	pthread_create(&checker, NULL, check_death, &params);
	join_threads(philo_threads, params.nb_philos);
	pthread_join(checker, NULL);
	free(philo_threads);
	destroy_mutexes(&params);
	free_params(&params);
	return (0);
}

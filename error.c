/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:28:31 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 17:28:49 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	input_err_exit(void)
{
	printf("use: ./philo number_of_philos time_to_die time_to_eat time_to_sleep\
 [number_of_meals]\n");
	exit(EXIT_FAILURE);
}

void	print_exit(const char *err_msg)
{
	printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

void	free_print_exit(const char *err_msg, t_params *params)
{
	destroy_mutexes(params);
	free_params(params);
	print_exit(err_msg);
}

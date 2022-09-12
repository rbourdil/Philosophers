/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:08:12 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 18:08:14 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*solo_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_action(philo->id, philo->params, FORK);
	free(arg);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:31:21 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/12 17:16:13 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_eat_sleep_time(char *s, const char *parameter_name)
{
	int	digits;

	if (*s == '-')
	{
		printf("%s cannot be a negative integer\n", parameter_name);
		input_err_exit();
	}
	if (*s == '+')
		s++;
	digits = 0;
	while (s[digits] != '\0')
	{
		if (!ft_isdigit(s[digits]))
		{
			printf("%s is not  valid integer\n", s);
			input_err_exit();
		}
		digits++;
	}
	if (digits >= 4)
	{
		printf("%s cannot be greater than or equal to 1000\n", parameter_name);
		input_err_exit();
	}
}	

static void	ft_isint(char *s, const char *parameter_name)
{
	int	digits;

	if (*s == '-')
	{
		printf("%s cannot be a negative integer\n", parameter_name);
		input_err_exit();
	}
	if (*s == '+')
		s++;
	digits = 0;
	while (s[digits] != '\0')
	{
		if (!ft_isdigit(s[digits]))
		{
			printf("%s is not a valid integer", s);
			input_err_exit();
		}
		digits++;
	}
	if (digits > 10 || (digits == 10 && ft_strcmp(s, INTMAX) > 0))
	{
		printf("%s must be a 32 bits integer\n", parameter_name);
		input_err_exit();
	}
}

void	check_args(int argc, char *argv[])
{
	ft_isint(argv[1], "number_of_philosophers");
	if (ft_strcmp(argv[1], "0") == 0)
	{
		printf("number_of_philosophers must be at least 1\n");
		input_err_exit();
	}
	ft_isint(argv[2], "time_to_die");
	check_eat_sleep_time(argv[3], "time_to_eat");
	check_eat_sleep_time(argv[4], "time_to_sleep");
	if (argc == 6)
		ft_isint(argv[5], "number_of_times_each_philosopher_must_eat");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:39:58 by rbourdil          #+#    #+#             */
/*   Updated: 2022/09/13 14:40:07 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

# define PAUSE 1500
# define MICRO_PAUSE 40
# define FORK 0x1
# define EAT 0x2
# define SLEEP 0x4
# define THINK 0x8
# define INTMAX "2147483647"

typedef struct s_params {
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	pthread_mutex_t	death_mutex;
	int				death;
	pthread_mutex_t	nb_done_eating_mutex;
	int				nb_done_eating;
	pthread_mutex_t	*time_of_death_mutexes;
	int				*time_of_death;
	pthread_mutex_t	*forks;
	int				start;
}	t_params;

typedef struct s_philo {
	int				id;
	t_params		*params;
}	t_philo;

/* init.c */

void	init_params(t_params *params, int argc, char *argv[]);

/* check_args.c */

void	check_args(int argc, char *argv[]);

/* start.c */

void	start_philo_threads(pthread_t *philo_threads, t_params *params);

/* eat_sleep_think.c */

void	*eat_sleep_think(void *arg);
void	*solo_philo(void *arg);

/* checker.c */

void	*check_death(void *arg);

/* utils.c */

int		now(void);
int		someone_died(t_params *params);
int		isdead(t_params *params, int id);
void	print_action(int id, t_params *params, int action);
void	done_eating(t_params *params);
int		everyone_done_eating(t_params *params);

/* free.c */

void	free_params(t_params *params);
void	destroy_mutexes(t_params *params);
void	join_threads(pthread_t *threads, int n);

/* error.c */

void	print_exit(const char *err_msg);
void	free_print_exit(const char *err_msg, t_params *params);
void	input_err_exit(void);

/* std_fts.c */

int		ft_isdigit(int c);
int		ft_strcmp(char *s1, char *s2);
void	ft_memset(void *s, int c, size_t n);	
int		ft_atoi(char *s);

#endif

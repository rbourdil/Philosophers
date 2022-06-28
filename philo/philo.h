/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:35:07 by rbourdil          #+#    #+#             */
/*   Updated: 2022/06/28 11:34:25 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define DEAD 1
# define ALIVE 0
# define FIRST 0x1
# define SECOND 0x2
# define FORK 0x1
# define EAT 0x2
# define SLEEP 0x4
# define THINK 0x8
# define PAUSE 1500
# define MAX_SLEEP "1000"
# define INTMAX "2147483647"

typedef struct s_common {
	pthread_mutex_t	dead_mutex;
	int				dead;
}	t_common;

typedef struct s_params {
	int				philo_id;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	struct s_common	*common;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				eat_count;
	long			death_date;
}	t_params;

void			*eat_sleep_think(void *args);
void			*alone(void *args);
int				print_action(t_params *params, int action);
void			release_forks(t_params *params, int opt);

pthread_mutex_t	*init_forks(int nb_philos);
pthread_t		*init_philos(char *argv[], pthread_mutex_t *forks, \
int nb_philos);

long			now(void);

void			join_philos(pthread_t *philos, int nb_philos);

int				check_args(int argc, char *argv[]);

int				ft_strlen(const char *s);
int				ft_isspace(const char c);
int				ft_isdigit(const char c);
int				ft_strcmp(const char *s1, const char *s2);

void			err_abort(const char *msg);

#endif

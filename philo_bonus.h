#ifndef PHILO_BONUS
#define PHILO_BONUS

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <string.h>

#define DEAD_SEM "/dead_sem"
#define FORKS_SEM "/forks_sem"
#define WAITER_SEM "/waiter_sem"
#define FORK 0x1
#define EAT 0x2
#define SLEEP 0x4
#define THINK 0x8

typedef struct s_args {
	unsigned int	nb_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				eat_count;
}	t_args;

typedef struct s_common {
	sem_t	*dead_sem;
	sem_t	*forks;
	sem_t	*waiter;
}	t_common;

void		eat_sleep_think(int philo_id, t_common *common, t_args *args, long death_date);

t_args		*init_args(int argc, char *argv[]);
t_common	*init_common(int nb_philos);

long		now(void);

void		err_abort(const char *msg);

#endif

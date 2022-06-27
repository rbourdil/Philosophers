#include "philo_bonus.h"

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	args->nb_philos = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		args->eat_count = atoi(argv[5]);
	else
		args->eat_count = -1;
	return (args);
}

t_common	*init_common(int nb_philos)
{
	t_common *common;

	sem_unlink(DEAD_SEM);
	sem_unlink(FORKS_SEM);
	sem_unlink(WAITER_SEM);
	common = (t_common *)malloc(sizeof(t_common));
	if (common == NULL)
		return (NULL);
	common->dead_sem = sem_open(DEAD_SEM, O_CREAT, 0644, 1);
	if (common->dead_sem == SEM_FAILED)
	{
		free(common);
		return (NULL);
	}
	common->forks = sem_open(FORKS_SEM, O_CREAT, 0644, nb_philos);
	if (common->forks == SEM_FAILED)
	{
		sem_close(common->dead_sem);
		free(common);
		return (NULL);
	}
	common->waiter = sem_open(WAITER_SEM, O_CREAT, 0644, 1);
	//security
	return (common);
}

#include "philo_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_args		*args;
	pid_t		*cpid;
	t_common	*common;
	int			i;

	if (argc < 5 || argc > 6)
		err_abort("Invalid number of arguments\n");
	args = init_args(argc, argv);
	if (args == NULL)
		err_abort("Failed to initialize arguments\n");
	common = init_common(args->nb_philos);
	if (common == NULL)
	{
		free(args);
		err_abort("Failed to open semaphores\n");
	}
	cpid = (pid_t *)malloc(sizeof(pid_t) * args->nb_philos);
	//if cpid == NULL ...
	i = 0;
	while (i < args->nb_philos)
	{
		cpid[i] = fork();
		if (cpid[i] == -1)
		{
			//kill and clean
			free(args);
			err_abort("A process fork failed\n");
		}
		else if (cpid[i] == 0)
			eat_sleep_think(i + 1, common, args, now() + args->time_to_die);
		i++;
	}
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < args->nb_philos)
		kill(cpid[i++], SIGKILL);
	sem_close(common->forks);
	sem_close(common->dead_sem);
	sem_close(common->waiter);
	sem_unlink(FORKS_SEM);
	sem_unlink(DEAD_SEM);
	sem_unlink(WAITER_SEM);
	return (0);
}

#include "philo_bonus.h"

void	print_action(int action, int philo_id)
{
	if ((action & FORK) != 0)
		printf("%ld %d has taken a fork\n", now(), philo_id);
	else if ((action & EAT) != 0)
		printf("%ld %d is eating\n", now(), philo_id);
	else if ((action & SLEEP) != 0)
		printf("%ld %d is sleeping\n", now(), philo_id);
	else if ((action & THINK) != 0)
		printf("%ld %d is thinking\n", now(), philo_id);
}

void	check_and_print(t_common *common, int philo_id, int death_date, int action)
{
	sem_wait(common->dead_sem);
	if (death_date < now())
	{
		printf("%ld %d died\n", now(), philo_id);
		exit(EXIT_SUCCESS);
	}
	else
		print_action(action, philo_id);
	sem_post(common->dead_sem);
}

void	eat_sleep_think(int philo_id, t_common *common, t_args *args, long death_date)
{
	while (1)
	{
		sem_wait(common->waiter);
		sem_wait(common->forks);
		check_and_print(common, philo_id, death_date, FORK);
		sem_wait(common->forks);
		sem_post(common->waiter);
		check_and_print(common, philo_id, death_date, FORK);
		check_and_print(common, philo_id, death_date, EAT);
		death_date = now() + args->time_to_die;
		usleep(args->time_to_eat * 1000);
		sem_post(common->forks);
		sem_post(common->forks);
		check_and_print(common, philo_id, death_date, SLEEP);
		usleep(args->time_to_sleep * 1000);
		check_and_print(common, philo_id, death_date, THINK);
	}
}

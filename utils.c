#include "philo.h"

int	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	someone_died(t_params *params)
{
	int	status;

	pthread_mutex_lock(&params->death_mutex);
	status = params->death;
	pthread_mutex_unlock(&params->death_mutex);
	return (status);
}

int	isdead(t_params *params, int id)
{
	pthread_mutex_lock(&params->time_of_death_mutexes[id]);
	if (params->time_of_death[id] < now())
	{
		pthread_mutex_unlock(&params->time_of_death_mutexes[id]);
		pthread_mutex_lock(&params->death_mutex);
		params->death = 1;
		pthread_mutex_unlock(&params->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&params->time_of_death_mutexes[id]);
	return (0);
}

void	print_action(int id, t_params *params, int action)
{
	pthread_mutex_lock(&params->death_mutex);
	if (params->death == 1)
	{
		pthread_mutex_unlock(&params->death_mutex);
		return ;
	}
	if ((action & FORK) != 0)
		printf("%d %d has taken a fork\n", now() - params->start, id + 1);
	else if ((action & EAT) != 0)
		printf("%d %d is eating\n", now() - params->start, id + 1);
	else if ((action & SLEEP) != 0)
		printf("%d %d is sleeping\n", now() - params->start, id + 1);
	else if ((action & THINK) != 0)
		printf("%d %d is thinking\n", now() - params->start, id + 1);
	pthread_mutex_unlock(&params->death_mutex);
}

void	done_eating(t_params *params)
{
	pthread_mutex_lock(&params->nb_done_eating_mutex);
	params->nb_done_eating++;
	pthread_mutex_unlock(&params->nb_done_eating_mutex);
}

int	everyone_done_eating(t_params *params)
{
	pthread_mutex_lock(&params->nb_done_eating_mutex);
	if (params->nb_done_eating == params->nb_philos)
	{
		pthread_mutex_unlock(&params->nb_done_eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(&params->nb_done_eating_mutex);
	return (0);
}

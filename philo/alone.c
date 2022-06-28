#include "philo.h"

void	*alone(void *args)
{
	t_params	*params;

	params = (t_params *)args;
	pthread_mutex_lock(params->first);
	if (print_action(params, FORK) == DEAD)
		return (NULL);
	usleep((params->death_date - now()) * 1000);	
	release_forks(params, FIRST);
	printf("%ld %d died\n", now(), params->philo_id);
	return (params);
}

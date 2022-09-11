#include "philo.h"

void	start_philo_threads(pthread_t *threads, t_params *params)
{
	t_philo		*philo;
	int			status;
	int			i;

	params->start = now();
	i = 0;
	while (i < params->nb_philos)
	{
		philo = malloc(sizeof(t_philo));
		if (philo == NULL)
		{
			join_threads(threads, i);
			free(threads);
			free_print_exit("memory allocation failed", params);
		}
		philo->id = i;
		philo->params = params;
		params->time_of_death[i] = params->start + params->time_to_die;
		if (params->nb_philos == 1)
			status = pthread_create(&threads[i], NULL, solo_philo, philo);
		else
			status = pthread_create(&threads[i], NULL, eat_sleep_think, philo);
		if (status != 0)
		{
			join_threads(threads, i);
			free(threads);
			free(philo);
			free_print_exit("thread creation failed", params);
		}
		i++;
	}
}

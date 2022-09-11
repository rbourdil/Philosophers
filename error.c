#include "philo.h"

void	print_exit(const char *err_msg)
{
	printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

void	free_print_exit(const char *err_msg, t_params *params)
{
	destroy_mutexes(params);
	free_params(params);
	print_exit(err_msg);
}

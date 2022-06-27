#include "philo_bonus.h"

void	err_abort(const char *msg)
{
	write(STDERR_FILENO, msg, strlen(msg));
	exit(EXIT_FAILURE);
}

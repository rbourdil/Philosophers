#include "philo_bonus.h"

long	now(void)
{
	struct timeval	tv;
	static long		start = 0;

	gettimeofday(&tv, NULL);
	if (start == 0)
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start);
}

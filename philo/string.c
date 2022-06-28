#include "philo.h"

int	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	return (p - s);
}

int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' ||\
c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_isdigit(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

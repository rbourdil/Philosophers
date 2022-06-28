#include "philo.h"

static int	is_int(char *arg)
{
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		arg++;
	if (!ft_isdigit(*arg))
		return (0);
	while (ft_isdigit(*arg))
		arg++;
	if (*arg != '\0')
		return (0);
	return (1);
}

static int	numcmp(const char *op1, const char *op2)
{
	if (*op1 == '-' && *op2 == '-')
	{
		op1++;
		op2++;
		if (ft_strlen(op1) != ft_strlen(op2))
			return (ft_strlen(op2) - ft_strlen(op1));
		return (ft_strcmp(op1, op2) * -1);
	}
	else if (*op1 == '-')
		return (-1);
	else if (*op2 == '-')
		return (1);
	if (ft_strlen(op1) != ft_strlen(op2))
		return (ft_strlen(op1) - ft_strlen(op2));
	return (ft_strcmp(op1, op2));
}

int	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_int(argv[i]))
			return (-1);
		i++;
	}
	if (numcmp(argv[1], "0") <= 0 || numcmp(argv[1], INTMAX) > 0)
		return (-1);
	i = 2;
	while (i < 5)
	{
		if (numcmp(argv[i], "0") < 0 || numcmp(argv[i], MAX_SLEEP) >= 0)
			return (-1);
		i++;
	}
	if (argc == 6)
		if (numcmp(argv[5], "0") < 0 || numcmp(argv[5], INTMAX) > 0)
			return (-1);
	return (0);
}

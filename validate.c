#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	check_av(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_arguments(t_simulation *sim, int argc, char **argv)
{
	sim->n_philo = atoi(argv[1]);
	sim->time_die = atoi(argv[2]);
	sim->time_eat = atoi(argv[3]);
	sim->time_sleep = atoi(argv[4]);
	if (sim->n_philo < 1 || sim->time_die < 1
		|| sim->time_eat < 1)
	{
		return (0);
	}
	if (argc == 6)
	{
		sim->meals_limit = atoi(argv[5]);
		if (sim->meals_limit < 1)
			return (0);
	}
	else
		sim->meals_limit = -1;
	return (1);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


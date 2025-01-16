#include "philosophers.h"

int	initialize_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->n_philo);
	if (!sim->forks)
		return (0);
	pthread_mutex_init(&sim->mutex_status, NULL);
	while (i < sim->n_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			free(sim->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

void    initialize_all(t_philo *philo, t_simulation *sim)
{
    int     i;

    i = -1;
    if (!initialize_forks(sim))
        return ;
    while (++i < sim->n_philo)
    {
        philo[i].id = i + 1;
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % sim->n_philo;
        philo[i].sim = sim;
    }
    i = -1;
    while (++i < sim->n_philo)
		pthread_create(&philo[i].threads, NULL, philo_routine, &philo[i]);
	//  i = -1;
	// pthread_create(&philo->death_thread, NULL, verify_death, philo);
    // while (++i < sim->n_philo)
	// 	pthread_join(philo[i].threads, NULL);
	// i = -1;
	// while (++i < table->n_philo)
	// 	pthread_join(philo[i].thread, NULL);
	// pthread_join(philo->death_thread, NULL

}
t_simulation	*init_struct_simulation(void)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	memset(sim, 0, sizeof(t_simulation));
	return (sim);
}

t_philo	*init_struct_philo(int n_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * n_philo);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->start_time = get_current_time();
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_simulation	*sim;

	if (argc != 4 && argc != 5)
	{
		printf("Uso:philo \n");
		return (1);
	}
	if (!check_av(argc, argv))
	{
		printf("Uso:error \n");
		return (1);
	}
	philo = init_struct_philo(atoi(argv[1]));
	sim = init_struct_simulation();
	if (!validate_arguments(sim, argc, argv))
	{
		printf("Erro");
		return (1);
	}
	initialize_all(philo, sim);
	free(philo);
	return (0);
}

#include "philosophers.h"

int validate_arguments(int argc)
{
    if (argc < 5 || argc > 6)
    {
        printf("Uso: ./philo num_filosofos tempo_morrer tempo_comer tempo_dormir [num_refeicoes]\n");
        return (0);
    }
    return (1);
}

void parse_arguments(t_simulation *sim, int argc, char **argv)
{
    sim->num_philosophers = atoi(argv[1]);
    sim->time_to_die = atoi(argv[2]);
    sim->time_to_eat = atoi(argv[3]);
    sim->time_to_sleep = atoi(argv[4]);

    if (argc == 6)
        sim->meals_limit = atoi(argv[5]);
    else
        sim->meals_limit = -1;
}
int allocate_simulation_memory(t_simulation *sim)
{
    sim->philosophers = malloc(sim->num_philosophers * sizeof(t_philosopher));
    sim->forks = malloc(sim->num_philosophers * sizeof(pthread_mutex_t));

    if (!sim->philosophers || !sim->forks)
    {
        free(sim->philosophers);
        free(sim->forks);
        return (0);
    }
    return (1);
}

void initialize_forks(t_simulation *sim)
{
    int i = 0;

    while (i < sim->num_philosophers)
    {
        pthread_mutex_init(&sim->forks[i], NULL);
        i++;
    }
}

void initialize_philosophers(t_simulation *sim)
{
    int i = 0;

    while (i < sim->num_philosophers)
    {
        sim->philosophers[i].id = i + 1;
        sim->philosophers[i].eat_count = 0;
        sim->philosophers[i].last_meal_time = get_current_time();
        sim->philosophers[i].left_fork = &sim->forks[i];
        sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim->num_philosophers];
        i++;
    }
}
long get_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

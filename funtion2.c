#include "philosophers.h"

void take_forks(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_simulation *sim = philo->simulation;

    while (1)
    {
        take_forks(philo);
        printf("%ld %d is eating\n", get_current_time(), philo->id);
        usleep(sim->time_to_eat * 1000);
        
        philo->last_meal_time = get_current_time();
        philo->eat_count++;

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        printf("%ld %d is sleeping\n", get_current_time(), philo->id);
        usleep(sim->time_to_sleep * 1000);

        printf("%ld %d is thinking\n", get_current_time(), philo->id);

        if (sim->meals_limit > 0 && philo->eat_count >= sim->meals_limit)
            break;
    }
    return (NULL);
}
void create_threads(t_simulation *sim)
{
    pthread_t *threads;
    int i = 0;

    threads = malloc(sim->num_philosophers * sizeof(pthread_t));
    
    while (i < sim->num_philosophers)
    {
        sim->philosophers[i].simulation = sim;
        pthread_create(&threads[i], NULL, philosopher_routine, &sim->philosophers[i]);
        i++;
    }
    
    sim->threads = threads;
}

void monitor_philosophers(t_simulation *sim)
{
    long current_time;
    int i;

    while (1)
    {
        i = 0;
        while (i < sim->num_philosophers)
        {
            current_time = get_current_time();
            if (current_time - sim->philosophers[i].last_meal_time > sim->time_to_die)
            {
                printf("%ld %d died\n", current_time, sim->philosophers[i].id);
                return;
            }
            i++;
        }
        usleep(1000);
    }
}
void cleanup_simulation(t_simulation *sim)
{
    int i = 0;

    while (i < sim->num_philosophers)
    {
        pthread_join(sim->threads[i], NULL);
        i++;
    }

    i = 0;
    while (i < sim->num_philosophers)
    {
        pthread_mutex_destroy(&sim->forks[i]);
        i++;
    }

    free(sim->philosophers);
    free(sim->forks);
    free(sim->threads);
}

     #include "philosophers.h"
    
void	print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->sim->mutex_status);
	printf("%ld -> %d %s \n", get_current_time() - philo->start_time,
		philo->id, status);
    pthread_mutex_unlock(&philo->sim->mutex_status);
}

void take_forks(t_philo *philo, t_simulation *sim)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&sim->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&sim->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&sim->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&sim->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
    }
}

void drop_forks(t_philo *philo, t_simulation *sim)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&sim->forks[philo->left_fork]);
        pthread_mutex_unlock(&sim->forks[philo->right_fork]);
    }
    else
    {
        pthread_mutex_unlock(&sim->forks[philo->right_fork]);
        pthread_mutex_unlock(&sim->forks[philo->left_fork]);
    }
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    t_simulation *sim;

    philo = (t_philo *)arg;
    sim = philo->sim;
    while (1)
    {
        take_forks(philo, sim);
        // pthread_mutex_lock(&philo->sim->alive_mutex);
        // if (!philo->sim->is_alive)
        // {
        //     pthread_mutex_unlock(&philo->sim->alive_mutex);
        //     drop_forks(philo, sim);
        //     return (0);
        // }
        // pthread_mutex_unlock(&philo->sim->alive_mutex);
        print_status(philo, "is eating");
        usleep(sim->time_eat * 1000);
        // philo->last_meal_time = get_current_time();
        //  philo->n_eat++;
        drop_forks(philo, sim);
        print_status(philo, "is sleeping");
        usleep(sim->time_sleep * 1000);
        print_status(philo, "is thinking");
    }
    return (NULL);
}

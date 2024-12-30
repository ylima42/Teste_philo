#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher {
    int             id;
    int             eat_count;
    long            last_meal_time;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    struct s_simulation *simulation;
} t_philosopher;

typedef struct s_simulation {
    int             num_philosophers;
    int             meals_limit;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    t_philosopher   *philosophers;
    pthread_mutex_t *forks;
    pthread_t       *threads;
} t_simulation;

int     validate_arguments(int argc);
void    parse_arguments(t_simulation *sim, int argc, char **argv);
int     allocate_simulation_memory(t_simulation *sim);
void    initialize_forks(t_simulation *sim);
void    initialize_philosophers(t_simulation *sim);
long    get_current_time(void);
void    *philosopher_routine(void *arg);
void    create_threads(t_simulation *sim);
void    monitor_philosophers(t_simulation *sim);
void    cleanup_simulation(t_simulation *sim);

#endif

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_Ho999

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
#include <unistd.h>

typedef struct s_simulation
{
	int					n_philo;
	int					meals_limit;
	int					is_alive;	
	long				time_eat;
	long				time_die;
	long				time_sleep;
	pthread_mutex_t		*forks;
	pthread_mutex_t mutex_status;
	pthread_mutex_t		alive_mutex;
}						t_simulation;

typedef struct s_philo
{
	int					id;
	int					n_eat;
	long				start_time;
	int					right_fork;
	int					left_fork;
	long				last_meal_time;
	t_simulation	*sim;
	pthread_t			threads;
}						t_philo;

long					get_current_time(void);
int						check_av(int argc, char **argv);
t_philo	*init_philo(int n_philo);
int						validate_arguments(t_simulation *sim, int argc,
							char **argv);
void    initialize(t_philo *philo, t_simulation *sim);
void *philo_routine(void *arg);


#

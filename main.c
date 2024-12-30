#include "philosophers.h"

int main(int argc, char **argv)
{
    t_simulation simulation;

    if (!validate_arguments(argc))
        return (1);

    parse_arguments(&simulation, argc, argv);

    if (!allocate_simulation_memory(&simulation))
        return (1);

    initialize_forks(&simulation);
    initialize_philosophers(&simulation);
    
    create_threads(&simulation);
    monitor_philosophers(&simulation);
    cleanup_simulation(&simulation);

    return (0);
}

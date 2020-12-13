
#include "philo.h"

int clean_exit(int status)
{
	int i;

	i = 0;
	if (g_philo)
	{
		while (i < g_philo->nb_philo)
		{
			pthread_mutex_destroy(&g_philo->forks[i]);
			++i;
		}
		free(g_philo->threads);
		g_philo->threads = NULL;
		free(g_philo->forks);
		g_philo->forks = NULL;
		free(g_philo->last_eaten);
		g_philo->last_eaten = NULL;
		free(g_philo->has_eaten);
		g_philo->has_eaten = NULL;
		free(g_philo);
	}
	g_philo = NULL;

	return (status);
}
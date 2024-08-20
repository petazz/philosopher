/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:24 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:26:01 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->n_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (printf("error join\n"), 1);
		i++;
	}
	return (0);
}

int	create_philos(t_data *data, t_philos *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		init_philos(&philos[i], forks, i, data);
	data->time = get_current_time();
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine_philo,
				(void *)&philos[i]) != 0)
			return (printf("error  create philos\n"), 1);
		i++;
	}
	create_monitor(philos);
	return (0);
}

void	*one_philo_routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	pthread_mutex_lock(philos->fork_1);
	print_str("has taken a fork", philos);
	pthread_mutex_unlock(philos->fork_1);
	ft_usleep(philos->data->time_to_die);
	print_str("died", philos);
	return (NULL);
}

int	one_philo(t_philos *philos, pthread_mutex_t *forks, t_data *data)
{
	init_philos(&philos[0], forks, 0, data);
	data->time = get_current_time();
	if (pthread_create(&philos[0].thread, NULL, one_philo_routine,
			(void *)&philos[0]) != 0)
		return (printf("error create philos\n"));
	if (pthread_join(philos->thread, NULL) != 0)
		return (printf("error join\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos		*philos;
	t_data			data;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (printf("Error in the numeric arguments\n"), 0);
	init_struct(&data);
	if (valid_arguments(argc, argv, &data) == 0)
		return (1);
	philos = malloc(sizeof(t_philos) * data.n_philos);
	if (!philos)
		return (1);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.n_philos);
	if (!forks)
		return (1);
	init_forks(&data, forks);
	if (data.n_philos == 1)
		one_philo(philos, forks, &data);
	else
	{
		if (create_philos(&data, philos, forks) == 1)
			return (printf("Error creating threads\n"), 1);
		join_threads(philos);
	}
	free_philos(philos, forks);
}

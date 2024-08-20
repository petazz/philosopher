/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:06:24 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:25:29 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_struct(t_data *data)
{
	data->n_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_times_to_eat = 0;
	data->dead_flag = 0;
	data->meals_finish = 0;
	data->time = 0;
	pthread_mutex_init(&data->meal_finish_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}

void	init_philos(t_philos *philos, pthread_mutex_t *forks, int i,
		t_data *data)
{
	philos->id = i + 1;
	philos->last_time_to_eat = 0;
	philos->count_eat = 0;
	philos->fork_1 = &forks[i];
	philos->fork_2 = &forks[(i + 1) % data->n_philos];
	philos->data = data;
	philos->philo_full = 0;
	pthread_mutex_init(&philos->count_eat_lock, NULL);
	pthread_mutex_init(&philos->philo_full_lock, NULL);
	pthread_mutex_init(&philos->last_time_to_eat_lock, NULL);
}

int	valid_arguments(int argc, char **argv, t_data *data)
{
	data->n_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_times_to_eat = 0;
	if (argc == 6 && data->num_times_to_eat == 0)
		return (0);
	else if (argc == 6 && data->num_times_to_eat < 0)
	{
		printf("Error in the arguments\n");
		return (0);
	}
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->n_philos <= 0)
	{
		printf("Error in the arguments\n");
		return (0);
	}
	return (1);
}

void	init_forks(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	free_philos(t_philos *philos, pthread_mutex_t *forks)
{
	free(philos);
	free(forks);
}

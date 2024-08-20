/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:06:13 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:17:49 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_philos *philos)
{
	print_str("is sleeping", philos);
	ft_usleep(philos->data->time_to_sleep);
}

void	philo_think(t_philos *philos)
{
	print_str("is thinking", philos);
}

void	take_fork(t_philos *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->fork_1);
		print_str("has taken a fork", philos);
		pthread_mutex_lock(philos->fork_2);
		print_str("has taken a fork", philos);
	}
	else
	{
		pthread_mutex_lock(philos->fork_2);
		print_str("has taken a fork", philos);
		pthread_mutex_lock(philos->fork_1);
		print_str("has taken a fork", philos);
	}
}

void	*routine_philo(void *pointer)
{
	t_philos	*philos;

	philos = (t_philos *)pointer;
	if (philos->id % 2 == 0)
		ft_usleep(10);
	while (!is_dead(philos) && !is_full(philos))
	{
		if (!is_dead(philos))
			philo_eat(philos);
		if (!is_dead(philos))
			philo_sleep(philos);
		if (!is_dead(philos))
			philo_think(philos);
		if (philos->id % 2 != 0)
			ft_usleep(10);
	}
	return (NULL);
}

void	philo_eat(t_philos *philos)
{
	take_fork(philos);
	print_str("is eating", philos);
	pthread_mutex_lock(&philos->count_eat_lock);
	philos->count_eat++;
	if (philos->data->num_times_to_eat
		&& philos->count_eat >= philos->data->num_times_to_eat)
		set_full(philos);
	pthread_mutex_unlock(&philos->count_eat_lock);
	pthread_mutex_lock(&philos->last_time_to_eat_lock);
	philos->last_time_to_eat = (get_current_time() - philos->data->time);
	pthread_mutex_unlock(&philos->last_time_to_eat_lock);
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(philos->fork_1);
	pthread_mutex_unlock(philos->fork_2);
}

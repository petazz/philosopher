/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:51:44 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:18:26 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philos *philos)
{
	int	dead;

	pthread_mutex_lock(&philos->data->dead_lock);
	dead = philos->data->dead_flag;
	pthread_mutex_unlock(&philos->data->dead_lock);
	return (dead);
}

void	set_full(t_philos *philos)
{
	pthread_mutex_lock(&philos->philo_full_lock);
	philos->philo_full = 1;
	pthread_mutex_unlock(&philos->philo_full_lock);
}

int	is_full(t_philos *philo)
{
	int	full;

	pthread_mutex_lock(&philo->philo_full_lock);
	full = philo->philo_full;
	pthread_mutex_unlock(&philo->philo_full_lock);
	return (full);
}

int	check_full(t_philos *philos)
{
	int	i;
	int	meals_finish;

	i = 0;
	meals_finish = 0;
	while (i < philos->data->n_philos)
	{
		if (is_full(&philos[i]))
		{
			meals_finish++;
		}
		i++;
	}
	if (meals_finish == philos->data->n_philos)
		return (1);
	return (0);
}

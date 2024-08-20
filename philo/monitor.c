/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:46:01 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:19:38 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_monitor(t_philos *philos)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, routine_monitor, (void *)philos) != 0)
		return (printf("error  create monitor\n"), 1);
	if (pthread_join(monitor, NULL) != 0)
		return (printf("error  join monitor\n"), 1);
	return (0);
}

void	*routine_monitor(void *arg)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)arg;
	while (!is_dead(philos) && !check_full(philos))
	{
		i = -1;
		while (++i < philos->data->n_philos)
		{
			pthread_mutex_lock(&philos[i].last_time_to_eat_lock);
			if (((get_current_time() - philos->data->time)
					- philos[i].last_time_to_eat) > philos->data->time_to_die)
			{
				pthread_mutex_unlock(&philos[i].last_time_to_eat_lock);
				print_str("died", &philos[i]);
				pthread_mutex_lock(&philos[i].data->dead_lock);
				philos[i].data->dead_flag = 1;
				pthread_mutex_unlock(&philos[i].data->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].last_time_to_eat_lock);
		}
		ft_usleep(10);
	}
	return (NULL);
}

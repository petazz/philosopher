/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:46:01 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/15 20:45:07 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		create_monitor(t_philos *philos)
{
	pthread_t	*monitor;

	if (pthread_create(monitor, NULL, routine_monitor, (void *)&philos) != 0)
		return (printf("error  create monitor\n"), 1);/* destroy_all("Error creating threads", philos); */
	if (pthread_join(philos->thread, NULL) != 0)
		return (printf("error  join monitor\n"), 1);/* destroy_all("Error creating threads", philos); */
	return (0);
}

int	routine_monitor(t_philos *philos)
{
	printf("AAAAAAAAAAAAAAAA\n");
	// while(!is_dead(philos))
    // {
	// 	if ()
    // }
}
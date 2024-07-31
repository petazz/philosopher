/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:06:13 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/31 19:19:38 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    philo_sleep(t_philos *philos)
{
    printf("%d %d is sleeping", get_current_time(philos), philos->id);
    usleep(philos->time_to_sleep);
}

void    philo_think(t_philos *philos)
{
    printf("%d %d is thinking", get_current_time(philos), philos->id);
}

void    philo_eat(t_philos *philos)
{
    pthread_mutex_lock(philos->forks)
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:06:13 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/15 21:33:21 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    philo_sleep(t_philos *philos)
{
    print_str("is sleeping",philos);
    ft_usleep(philos->data->time_to_sleep);
}

void    philo_think(t_philos *philos)
{
    print_str("is thinking",philos);
}

void    take_fork(t_philos *philos)
{
    if (philos->id % 2 == 0)
    {
        pthread_mutex_lock(philos->fork_1);
        print_str("has taken a fork", philos);
        pthread_mutex_lock(philos->fork_2);
        print_str("has taken the second fork", philos);
    }
    else
    {
        pthread_mutex_lock(philos->fork_2);
        print_str("has taken the second fork", philos);   
        pthread_mutex_lock(philos->fork_1);
        print_str("has taken a fork", philos);
    }
}

void    philo_eat(t_philos *philos)
{
    take_fork(philos);
    print_str("is eating", philos);
    pthread_mutex_lock(&philos->count_eat_lock);
    philos->count_eat++;
    pthread_mutex_unlock(&philos->count_eat_lock);
    pthread_mutex_lock(&philos->last_time_to_eat_lock);
    philos->last_time_to_eat = get_current_time();
    pthread_mutex_unlock(&philos->last_time_to_eat_lock);
    ft_usleep(philos->data->time_to_eat);
    pthread_mutex_unlock(philos->fork_1);
    pthread_mutex_unlock(philos->fork_2);
}
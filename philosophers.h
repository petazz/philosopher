/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philossophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:30 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/25 04:00:58 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philosSOPHERS_H
# define philosSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philos
{
    pthread_t       thread;
    pthread_mutex_t *forks;
    int             id;
    int             *dead;
    int             n_philos;
    size_t             time_to_die;
    size_t             time_to_eat;
    size_t             time_to_sleep;
    size_t             num_times_to_eat;
}   t_philos;

typedef struct s_data
{
    int     dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;    
}   t_data;

void    init_struct(t_philos *philos);
void    valid_arguments(char **argv, t_philos *philos);
t_philos* new_node();
void    push(t_philos **philo);
void    create_philoss(t_philos *philos);
int     ft_atoi(const char *str);

#endif
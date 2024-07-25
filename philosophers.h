/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datasophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:30 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/25 04:00:58 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef dataSOPHERS_H
# define dataSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    pthread_mutex_t *forks;
    int n_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_must_eat;
    struct s_data *next;
}   t_data;

void    init_struct(t_data *data);
void    valid_arguments(char **argv, t_data *data);
t_data    *new_node();
void    push(t_data **philo);
void    create_datas(t_data *data);
int	ft_atoi(const char *str);

#endif
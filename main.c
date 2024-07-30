/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:24 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/30 05:58:29 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void    init_struct(t_philos *philos)
// {
//     philos->forks = NULL;
//     philos->n_philos = 0;
//     philos->time_to_die = 0;
//     philos->time_to_eat = 0;
//     philos->time_to_sleep = 0;
//     philos->num_times_to_eat = 0;
// }

void    init_valid_arguments(char **argv, t_philos *philos)
{
    philos->n_philos = ft_atoi(argv[1]);
    if (philos->n_philos > 200 || philos->n_philos < 0)
        printf("Error in the numbers of philosophers\n");
    philos->time_to_die = ft_atoi(argv[2]);
    philos->time_to_eat = ft_atoi(argv[3]);
    philos->time_to_sleep = ft_atoi(argv[4]);
    if (philos->time_to_die < 60 || philos->time_to_eat < 60
        || philos->time_to_eat < 60)
        printf("Error in the numbers of time\n");
}

void    create_philos(t_philos *philos)
{
    int i;
    
    i = 0;
    while(i < philos->n_philos)
    {
        if (pthread_create(&philos[i], NULL, routine_philo, NULL) != 0);
            destroy_all("Error creating threads", philos);
        i++;
    }
    
}

void    init_forks(t_philos *philos, pthread_mutex_t *forks)
{
    int i;
    
    i = 0;
    while(i <= philos->n_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

int main (int argc, char **argv)
{
    t_philos    philos[ft_atoi(argv[1] + 1)];
    t_data      data;
    pthread_mutex_t forks[ft_atoi(argv[1])];
    
    if (argc != 5)
        return (printf("Error in the numeric arguments\n"), 0);
    //init_struct(&philos);
    init_valid_arguments(argv, &philos);
    init_forks(philos, forks);
    create_philos(&philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:24 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/15 21:40:54 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    init_struct(t_data *data)
{
    data->n_philos = 0;
    data->time_to_die = 0;
    data->time_to_eat = 0;
    data->time_to_sleep = 0;
    data->num_times_to_eat = 0;
    data->dead_flag = 0;
    data->time = 0;
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);
    pthread_mutex_init(&data->write_lock, NULL);
    
}

int		valid_arguments(char **argv, t_data *data)
{
    data->n_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (data->time_to_die < 0 || data->time_to_eat < 0
        || data->time_to_sleep < 0 || data->n_philos < 0)
	{
        printf("Error in the arguments\n");
		return (0);
	}
	return (1);
}

void    *routine_philo(void *pointer)
{
    t_philos *philos;

    philos = (t_philos *)pointer;
    if (philos->id % 2 == 0)
        ft_usleep(1);
    while(1)
    {
        philo_eat(philos);  
        philo_sleep(philos);
        philo_think(philos);
    }
	return (NULL);
}

void    init_philos(t_philos *philos, pthread_mutex_t *forks, int i, t_data *data)
{
	philos->id = i + 1;
	philos->last_time_to_eat = 0;
	philos->count_eat = 0;
	philos->fork_1 = &forks[i];
	philos->fork_2 = &forks[(i + 1) % data->n_philos];
    philos->data = data;
    philos->dead = 0;
    pthread_mutex_init(&philos->count_eat_lock, NULL);
    pthread_mutex_init(&philos->last_time_to_eat_lock, NULL);
}

int    create_philos(t_data *data, t_philos *philos, pthread_mutex_t *forks)
{
    int i;
    
    i = -1;
    while(++i < data->n_philos)
        init_philos(&philos[i], forks, i, data);
    data->time = get_current_time();
    i = 0;
    while(i < data->n_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, routine_philo,(void *)&philos[i]) != 0)
            return (printf("error  create philos\n"), 1);/* destroy_all("Error creating threads", philos); */
        i++;
    }
    return (0);
}

int join_threads(t_philos *philos)
{
    int i;

    i = 0;
    while (i < philos->data->n_philos)
    {
        if(pthread_join(philos[i].thread, NULL) != 0)
            return (printf("error join\n"), 1);/* destroy_all("Error creating threads", philos); */
        i++;
    }
    return (0);
}

void    init_forks(t_data *data, pthread_mutex_t *forks)
{
    int i;
    
    i = 0;
    while(i < data->n_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

int main (int argc, char **argv)
{
   	t_philos        *philos;
    t_data          data;
   	pthread_mutex_t *forks;
    
    if (argc != 5 && argc != 6)
        return (printf("Error in the numeric arguments\n"), 0);
    init_struct(&data);
    if (valid_arguments(argv, &data) == 0)
        return (1);
    philos = malloc(sizeof(t_philos) * data.n_philos);
	if (!philos)
		return (1);
    forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.n_philos);
	if (!forks)
		return (1);
    init_forks(&data, forks);
    create_philos(&data, philos, forks);
    //join_threads(philos);
	return (0);
}

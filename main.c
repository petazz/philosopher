/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:24 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/25 05:00:05 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    init_struct(t_data *data)
{
    data->forks = NULL;
    data->n_philos = 0;
    data->time_to_die = 0;
    data->time_to_eat = 0;
    data->time_to_sleep = 0;
    data->number_must_eat = 0;
}

void    valid_arguments(char **argv, t_data *data)
{
    data->n_philos = ft_atoi(argv[1]);
    if (data->n_philos > 200 || data->n_philos < 0)
        printf("Error in the numbers of philosophers\n");
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (data->time_to_die < 60 || data->time_to_eat < 60
        || data->time_to_eat < 60)
        printf("Error in the numbers of time\n");
}

t_data    *new_node()
{
    t_data *philo;

    philo = malloc(sizeof(t_data));
    if (!philo)
        return (NULL);
    philo->n_philos = 3;
    philo->time_to_die = 6;
    philo->time_to_eat = 0;
    philo->time_to_sleep = 0;
    philo->number_must_eat = 0;
    return (philo);
}

void    push(t_data **philo)
{
    t_data  *head;
    
    head = new_node();
    if(!head)
        head->next = head;
    else
        head->next = *philo;
    *philo = head;
    printf("%d\n", head->time_to_die);
}

void    create_datas(t_data *data)
{
    int i;
    
    i = 0;
    printf("%d\n", data->n_philos);
    while(i < data->n_philos)
    {
        printf("llega\n");
        push(&data);
        i++;
    }
}

int main (int argc, char **argv)
{
    t_data data;
    
    if (argc != 5)
        return (printf("Error in the numeric arguments\n"), 0);
    init_struct(&data);
    valid_arguments(argv, &data);
    create_datas(&data);
}

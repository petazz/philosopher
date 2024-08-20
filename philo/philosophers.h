/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:16:19 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:17:27 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_times_to_eat;
	int				meals_finish;
	int				dead_flag;
	long			time;
	pthread_mutex_t	meal_finish_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_data;

typedef struct s_philos
{
	pthread_t		thread;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_mutex_t	count_eat_lock;
	pthread_mutex_t	last_time_to_eat_lock;
	pthread_mutex_t	philo_full_lock;
	long			last_time_to_eat;
	long			count_eat;
	int				philo_full;
	int				id;
	t_data			*data;
}					t_philos;

void				init_struct(t_data *philos);
void				init_forks(t_data *data, pthread_mutex_t *forks);
int					valid_arguments(int argc, char **argv, t_data *philos);
t_philos			*new_node(void);
void				push(t_philos **philo);
int					create_philos(t_data *data, t_philos *philos, \
						pthread_mutex_t *forks);
long				ft_atoi(const char *str);
void				philo_sleep(t_philos *philos);
void				philo_think(t_philos *philos);
void				philo_eat(t_philos *philos);
int					is_dead(t_philos *philos);
void				print_str(char *str, t_philos *philo);
void				ft_usleep(int time);
void				print_str(char *str, t_philos *philo);
long				get_current_time(void);
void				take_fork(t_philos *philos);
int					create_monitor(t_philos *philos);
void				*routine_monitor(void *arg);
int					check_full(t_philos *philos);
int					is_full(t_philos *philo);
void				init_philos(t_philos *philos, pthread_mutex_t *forks, \
					int i, t_data *data);
void				set_full(t_philos *philos);
void				*routine_philo(void *pointer);
void				free_philos(t_philos *philos, pthread_mutex_t *forks);
void				*one_philo_routine(void *arg);
int					one_philo(t_philos *philos, pthread_mutex_t *forks,
						t_data *data);

#endif
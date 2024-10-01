/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:03 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/01 17:35:25 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

void *mz_routine(void *data)
{
	t_info	*philo;
	struct timeval 	time;
	time_t	t;
	time_t	x;
	x = get_time();
	
	philo = (t_info *)data;
	while (1)
	{
		t = get_time();
		printf("%ld X has taken a fork\n", get_time() - x);
		if (get_time() - t > philo->t_die)
			break ;
		printf("%ld X is eating\n", get_time() - x);
		mz_usleep(philo->t_eat);
		if (get_time() - t > philo->t_die)
			break ;
		printf("%ld X is sleeping\n", get_time() - x);
		mz_usleep(philo->t_sleep);
		if (get_time() - t > philo->t_die)
			break ;
		printf("%ld X is thinking\n", get_time() - x);
		if (get_time() - t > philo->t_die)
			break ;
	}
	
	printf("%ld X died\n", get_time() - x);
	return (NULL);
}

void	mz_init_philos(t_info *data)
{
	int i;
	
	data->philo = malloc(sizeof(t_philo) * (data->n_philo + 2));
	i = 0;
	while (i <= data->n_philo)
	{
		if (i == data->philo)
			data->philo[i]->id = 0;
		else
			data->philo[i]->id = i + 1;
		data->philo[i]->thread = malloc(sizeof(pthread_t));
		data->philo[i]->t_die = data->t_die;
		data->philo[i]->t_eat = data->t_eat;
		data->philo[i]->t_sleep = data->t_sleep;
		data->philo[i]->n_eat = data->n_eat;
		data->philo[i]->timestmp = data->timestmp;
		data->philo[i]->meals_eaten = 0;
	}
	data->philo[i] = NULL;
}

void	mz_init_forks(t_info *data)
{
	int i;

	data->fork = malloc(sizeof(t_fork) * (data->n_philo + 1));
	i = 0;
	while (i < data->n_philo)
	{
		data->fork[i]->id = i + 1;
		pthread_mutex_init(&data->fork[i]->fork, NULL);
	}
	data->fork[i] = NULL;
}

void	mz_init(t_info *data)
{
	mz_init_philos(data);
	mz_init_forks(data);
}

// philo_nbr = philo->dinner->num_of_philos;
// 	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
// 	philo->second_fork = &forks[philo_position];
// 	if (philo->id % 2 == 0)
// 	{
// 		philo->first_fork = &forks[philo_position];
// 		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
// 	}

int main(int ac, char **av)
{
    t_info  		data;
	pthread_t		*thread;
	int				i;

    if (mz_parser(ac, av, &data) == 1)
        return (1);
	mz_init(&data);










	thread = malloc(data.n_philo * sizeof(pthread_t) + 1 + 1);
	thread[data.n_philo + 1] = NULL;
	data.philo = thread;
	i = 0;
	while (i <= data.n_philo)
	{
		if (pthread_create(&thread[i], NULL, mz_routine, &data))
			return (1);
		i++;
	}
	i = 0;
	while (i <= data.n_philo)
	{
		if (pthread_join(thread[i], NULL))
			return (1);
		i++;
	}
	free(thread);
    return (0);
}



	// gettimeofday(&time, NULL);
	// printf("xx: %li\n", time.tv_sec * 1000 + time.tv_usec / 1000);
    // printf("XXXXXXXXXXXXXXXXXX\n");
    // printf("data->n_philo :%i\n", data.n_philo);
    // printf("data->t_die   :%i\n", data.t_die);
    // printf("data->t_eat   :%i\n", data.t_eat);
    // printf("data->t_sleep :%i\n", data.t_sleep);
    // printf("data->n_eat   :%i\n", data.n_eat);
    // printf("XXXXXXXXXXXXXXXXXX\n");
	
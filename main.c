/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:03 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/18 14:14:07 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mz_init_philos(t_info *data, int i)
{
	data->philo = malloc(sizeof(t_philo *) * (data->n_philo + 2));
	if (!data->philo)
		return (mz_free_forks(data, 1));
	while (i <= data->n_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (mz_philo_fail(data, i - 1, 0));
		data->philo[i]->id = i;
		if (i == data->n_philo)
			data->philo[i]->id = -1;
		data->philo[i]->meals_eaten = 0;
		data->philo[i]->fork_1 = data->fork[i];
		data->philo[i]->fork_2 = data->fork[(i + 1) % data->n_philo];
		data->philo[i]->data = data;
		if (pthread_mutex_init(&data->philo[i]->l_meal, NULL))
			return (mz_philo_fail(data, i - 1, 1));
		if (pthread_mutex_init(&data->philo[i]->meals_mtx, NULL))
			return (mz_philo_fail(data, i - 1, 2));
		i++;
	}
	data->philo[i] = NULL;
	return (0);
}

static int	mz_init_forks(t_info *data)
{
	int	i;

	data->fork = malloc(sizeof(t_fork *) * (data->n_philo + 1));
	if (!data->fork)
		return (mz_error_print(1));
	i = 0;
	while (i < data->n_philo)
	{
		data->fork[i] = malloc(sizeof(t_fork));
		if (!data->fork[i])
			return (mz_fork_fail(data, i, 1));
		data->fork[i]->id = i;
		if (pthread_mutex_init(&data->fork[i]->fork, NULL))
			return (mz_fork_fail(data, i, 0));
		i++;
	}
	data->fork[i] = NULL;
	return (0);
}

static int	mz_start(t_info *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo[i];
	data->timestmp = get_time();
	while (i < data->n_philo)
	{
		philo = data->philo[i];
		if (pthread_create(&data->philo[i]->thread, NULL, mz_routine1, philo))
			return (mz_thread_fail(data, i - 1));
		i++;
	}
	if (pthread_create(&data->philo[i]->thread, NULL, mz_routine_mon, data))
		return (mz_thread_fail(data, i - 1));
	return (0);
}

int	main(int ac, char **av)
{
	t_info	data;
	int		i;

	if (mz_parser(ac, av, &data))
		return (1);
	if (mz_init_forks(&data))
		return (1);
	if (mz_init_philos(&data, 0))
		return (1);
	if (mz_start(&data))
		return (1);
	i = 0;
	while (i <= data.n_philo)
	{
		pthread_join(data.philo[i]->thread, NULL);
		i++;
	}
	mz_free_forks(&data, 0);
	mz_free_philo(&data, 0);
	return (0);
}

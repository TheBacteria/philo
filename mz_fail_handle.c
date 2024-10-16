/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_fail_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:37:30 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/16 12:32:47 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mz_fork_fail(t_info *data, int i, int n)
{
	if (n == 0)
		free(data->fork[i]);
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&data->fork[i]->fork);
		free(data->fork[i]);
	}
	free(data->fork);
	return(mz_error_print(n));
}

int	mz_free_forks(t_info *data, int n)
{
	int i;

	i = 0;
	while(data->fork[i])
	{
		pthread_mutex_destroy(&data->fork[i]->fork);
		free(data->fork[i]);
		i++;
	}
	free(data->fork);
	if (n > 0)
		return (mz_error_print(n));
	return (0);
}

int mz_philo_fail(t_info *data, int i, int n)
{
	if (n == 1)
		free(data->philo[i]);
	else if (n == 2)
	{
		pthread_mutex_destroy(&data->philo[i]->l_meal);
		free(data->philo[i]);
	}
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->philo[i]->l_meal);
		pthread_mutex_destroy(&data->philo[i]->meals_mtx);
		free(data->philo[i]);
		i--;
	}
	free(data->philo);
	return (mz_free_forks(data, 1));
}

int mz_free_philo(t_info *data, int n)
{
	int i;

	i = 0;
	while (data->philo[i])
	{
		pthread_mutex_destroy(&data->philo[i]->l_meal);
		pthread_mutex_destroy(&data->philo[i]->meals_mtx);
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
	if (n > 0)
		return (mz_error_print(n));
	return (0);
}

int mz_thread_fail(t_info *data, int i)
{
	while (i >= 0)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i--;
	}
	mz_free_forks(data, 0);
	return (mz_free_philo(data, 2));
}
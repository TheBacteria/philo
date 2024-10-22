/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:53:33 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/16 12:54:12 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mz_check_death2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

int	mz_take_fork(t_philo *philo)
{
	if (mz_check_death2(philo))
		return (1);
	pthread_mutex_lock(&philo->fork_1->fork);
	if (mz_printer(philo, 1))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		return (1);
	}
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		mz_usleep(philo, philo->data->t_eat);
		return (1);
	}
	pthread_mutex_lock(&philo->fork_2->fork);
	if (mz_printer(philo, 1))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		return (1);
	}
	return (0);
}

int	mz_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->l_meal);
	if (mz_printer(philo, 3))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->meals_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mtx);
	mz_usleep(philo, philo->data->t_eat);
	pthread_mutex_unlock(&philo->fork_1->fork);
	pthread_mutex_unlock(&philo->fork_2->fork);
	return (0);
}

int	mz_sleep(t_philo *philo)
{
	if (mz_printer(philo, 2))
		return (1);
	mz_usleep(philo, philo->data->t_sleep);
	if (mz_printer(philo, 4))
		return (1);
	return (0);
}

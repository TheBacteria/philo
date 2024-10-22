/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:56:01 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/18 14:13:56 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	mz_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	pthread_mutex_lock(&philo->l_meal);
	if (get_time() - philo->last_meal > philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->l_meal);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->death);
		mz_printer(philo, 0);
		return (1);
	}
	pthread_mutex_unlock(&philo->l_meal);
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	*mz_philos_full(t_info *mon)
{
	pthread_mutex_lock(&mon->full);
	mon->is_full = 1;
	pthread_mutex_unlock(&mon->full);
	return (NULL);
}

void	*mz_routine_mon(void *data)
{
	int		i;
	int		j;
	t_info	*mon;

	mon = (t_info *)data;
	while (1)
	{
		i = 0;
		j = 0;
		while (i < mon->n_philo)
		{
			pthread_mutex_lock(&mon->philo[i]->meals_mtx);
			if (mon->philo[i]->meals_eaten < 0)
				j++;
			pthread_mutex_unlock(&mon->philo[i]->meals_mtx);
			if (mz_check_death(mon->philo[i]))
				return (NULL);
			i++;
		}
		if (j == mon->n_philo)
			return (mz_philos_full(mon));
	}
	return (NULL);
}

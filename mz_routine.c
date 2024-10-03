/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/03 15:48:25 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mz_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_1->fork);
	if (philo->is_dead == 1)
			return (1);
	printf("%ld %d has taken a fork\n", get_time() - philo->timestmp, philo->id);
	pthread_mutex_lock(&philo->fork_2->fork);
	if (philo->is_dead == 1)
			return (1);
	printf("%ld %d has taken a fork\n", get_time() - philo->timestmp, philo->id);
	if (get_time() - philo->last_meal > philo->t_die)
	{
		philo->is_dead = 1;
		printf("%ld %d died\n", get_time() - philo->timestmp, philo->id);
		return (1);
	}
	return (0);
}

int	mz_sleep(t_philo *philo)
{
	if (philo->is_dead == 1)
			return (1);
	printf("%ld %d is sleeping\n", get_time() - philo->timestmp, philo->id);
	mz_usleep(philo->t_sleep);
	if (get_time() - philo->last_meal > philo->t_die)
	{
		philo->is_dead = 1;
		printf("%ld %d died\n", get_time() - philo->timestmp, philo->id);
		return (1);
	}
	if (philo->is_dead == 1)
			return (1);
	printf("%ld %d is thinking\n", get_time() - philo->timestmp, philo->id);
	return (0);
}

int	mz_eat(t_philo *philo)
{
	if (philo->is_dead == 1)
			return (1);
	printf("%ld %d is eating\n", get_time() - philo->timestmp, philo->id);
	mz_usleep(philo->t_eat);
	pthread_mutex_unlock(&philo->fork_1->fork);
	pthread_mutex_unlock(&philo->fork_2->fork);
	philo->last_meal = get_time();
	return (0);
}

void *mz_routine1(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	philo->last_meal = get_time();
	if (philo->id % 2 == 0)
	{
		if(mz_sleep(philo))
			return (NULL);
	}
	while (1)
	{
		if(mz_take_fork(philo))
			break ;
		if (mz_eat(philo))
			break ;
		if(mz_sleep(philo))
			break ;
	}
	return (NULL);
}

void	mz_funeral(t_info *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i]->is_dead = 1;
		i++;
	}
}

void *mz_routineMon(void *data)
{
	int i;
	t_info *mon;
	
	mon = (t_info *)data;
	while (1)
	{
		i = 0;
		while (i < mon->n_philo)
		{
			if(mon->philo[i]->is_dead == 1)
			{
				printf("FUUUUUUUUUUUCK\n");
				mz_funeral(mon);
				return (NULL);
			}
			i++;
		}
	}
	
	return (NULL);
}
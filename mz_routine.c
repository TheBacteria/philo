/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/05 14:29:24 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	mz_printer(t_philo *philo, int n)
{
	pthread_mutex_lock(philo->printer);
	if (mz_check_death2(philo))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		pthread_mutex_unlock(philo->printer);
		return ;
	}
	if (n == 0)
	{
		printf("%lld %d died\n", get_time() - philo->timestmp, philo->id);
		return ;
	}
	else if (n == 1)
		printf("%lld %d has taken a fork\n", get_time() - philo->timestmp, philo->id);
	else if (n == 2)
		printf("%lld %d is sleeping\n", get_time() - philo->timestmp, philo->id);
	else if (n == 3)
		printf("%lld %d is eating\n", get_time() - philo->timestmp, philo->id);
	else if (n == 4)
		printf("%lld %d is thinking\n", get_time() - philo->timestmp, philo->id);
	else
		printf("Doesn't know what to print!\n");
	pthread_mutex_unlock(philo->printer);
}

int	mz_check_death2(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*(philo->is_dead) == 1)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}
int	mz_check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*(philo->is_dead) == 1)
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		pthread_mutex_unlock(philo->printer);
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	else if (get_time() - philo->last_meal >= philo->t_die || philo->meals_eaten >= philo->n_eat)
	{
		mz_printer(philo, 0);
		*(philo->is_dead) = 1;
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		pthread_mutex_unlock(philo->printer);
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->death);
	return (0);
}

int	mz_take_fork(t_philo *philo)
{
	if (mz_check_death2(philo))
		return (1);
	pthread_mutex_lock(&philo->fork_1->fork);
	if (mz_check_death2(philo))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		return (1);
	}
	mz_printer(philo, 1);
	pthread_mutex_lock(&philo->fork_2->fork);
	if (mz_check_death2(philo))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		return (1);
	}
	mz_printer(philo, 1);
	return (0);
}

int	mz_sleep(t_philo *philo)
{
	if (mz_check_death2(philo))
		return (1);
	mz_printer(philo, 2);
	mz_usleep(philo, philo->t_sleep);
	if (mz_check_death2(philo))
		return (1);
	mz_printer(philo, 4);
	return (0);
}

int	mz_eat(t_philo *philo)
{
	if (mz_check_death2(philo))
	{
		pthread_mutex_unlock(&philo->fork_1->fork);
		pthread_mutex_unlock(&philo->fork_2->fork);
		return (1);
	}
	philo->last_meal = get_time();
	mz_printer(philo, 3);
	philo->meals_eaten++;
	mz_usleep(philo, philo->t_eat);
	pthread_mutex_unlock(&philo->fork_1->fork);
	pthread_mutex_unlock(&philo->fork_2->fork);
	return (0);
}

void *mz_routine1(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	philo->last_meal = get_time();
	if (philo->id % 2 == 0)
	{
		mz_usleep(philo, 50);
	}
	while (1)
	{
		if (mz_check_death2(philo))
			break ;
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
		*(data->philo[i]->is_dead) = 1;
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
			if(mz_check_death(mon->philo[i]))
			{
				mz_funeral(mon);
				return (NULL);
			}
			i++;
		}
	}
	
	return (NULL);
}
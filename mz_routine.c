/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/13 12:44:34 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mz_printer(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->data->printer);
	if (n == 0)
	{
		printf("%lld %d died\n", get_time() - philo->data->timestmp, philo->id + 1);
		pthread_mutex_unlock(&philo->data->printer);
		return (1);
	}
	if (mz_check_death2(philo))
	{
		pthread_mutex_unlock(&philo->data->printer);
		return (1);
	}
	else if (n == 1)
		printf("%lld %d has taken a fork\n", get_time() - philo->data->timestmp, philo->id + 1);
	else if (n == 2)
		printf("%lld %d is sleeping\n", get_time() - philo->data->timestmp, philo->id + 1);
	else if (n == 3)
		printf("%lld %d is eating\n", get_time() - philo->data->timestmp, philo->id + 1);
	else if (n == 4)
		printf("%lld %d is thinking\n", get_time() - philo->data->timestmp, philo->id + 1);
	else
		printf("Doesn't know what to print!\n");
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}

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

void *mz_routine1(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->l_meal);
	philo->last_meal = philo->data->timestmp;
	pthread_mutex_unlock(&philo->l_meal);
	if (philo->id % 2 == 0)
		mz_usleep(philo, 50);
	while (1)
	{
		if(mz_take_fork(philo))
			break ;
		if (mz_eat(philo))
			break ;
		pthread_mutex_lock(&philo->meals_mtx);
		if ((philo->data->n_eat > -2 && philo->meals_eaten == philo->data->n_eat) || philo->meals_eaten < 0)
		{
			philo->meals_eaten = -2;
			pthread_mutex_unlock(&philo->meals_mtx);
			pthread_mutex_lock(&philo->data->full);
			if (philo->data->is_full == 1)
			{
				pthread_mutex_unlock(&philo->data->full);
				break ;
			}
			pthread_mutex_unlock(&philo->data->full);
		}
		pthread_mutex_unlock(&philo->meals_mtx);
		if(mz_sleep(philo))
			break ;
	}
	return (NULL);
}

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

void *mz_routineMon(void *data)
{
	int i;
	int j;
	t_info *mon;
	
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
			if(mz_check_death(mon->philo[i]))
				return (NULL);
			i++;
		}
		if (j == mon->n_philo)
		{
			pthread_mutex_lock(&mon->full);
			mon->is_full = 1;
			pthread_mutex_unlock(&mon->full);
			break ;
		}
	}
	return (NULL);
}

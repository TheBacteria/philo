/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/18 14:38:01 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	mz_printer(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->data->printer);
	philo->curr_t = get_time() - philo->data->timestmp;
	if (n == 0)
	{
		printf("%lld %d died\n", philo->curr_t, philo->id + 1);
		pthread_mutex_unlock(&philo->data->printer);
		return (1);
	}
	if (mz_check_death2(philo))
	{
		pthread_mutex_unlock(&philo->data->printer);
		return (1);
	}
	else if (n == 1)
		printf("%lld %d has taken a fork\n", philo->curr_t, philo->id + 1);
	else if (n == 2)
		printf("%lld %d is sleeping\n", philo->curr_t, philo->id + 1);
	else if (n == 3)
		printf("%lld %d is eating\n", philo->curr_t, philo->id + 1);
	else if (n == 4)
		printf("%lld %d is thinking\n", philo->curr_t, philo->id + 1);
	else
		printf("Doesn't know what to print!\n");
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}

int	mz_all_full(t_philo *philo)
{
	if ((philo->data->n_eat > -2 && philo->meals_eaten == philo->data->n_eat)
		|| philo->meals_eaten < 0)
	{
		philo->meals_eaten = -2;
		pthread_mutex_unlock(&philo->meals_mtx);
		pthread_mutex_lock(&philo->data->full);
		if (philo->data->is_full == 1)
		{
			pthread_mutex_unlock(&philo->data->full);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->full);
	}
	pthread_mutex_unlock(&philo->meals_mtx);
	return (0);
}

void	*mz_routine1(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->l_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->l_meal);
	if (philo->id % 2 == 0)
		mz_usleep(philo, 50);
	while (1)
	{
		if (mz_take_fork(philo))
			break ;
		if (mz_eat(philo))
			break ;
		pthread_mutex_lock(&philo->meals_mtx);
		if (mz_all_full(philo))
			return (NULL);
		if (mz_sleep(philo))
			break ;
	}
	return (NULL);
}

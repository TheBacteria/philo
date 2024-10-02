/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:10 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/02 19:13:36 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *mz_routine1(void *data)
{
	t_philo	*philo;
	struct timeval 	time;
	time_t	t;
	
	philo = (t_philo *)data;
	while (1)
	{
		// t = get_time();
		printf("%ld X has taken a fork\n", get_time() - philo->timestmp);
		// if (get_time() - t > philo->t_die)
		// 	break ;
		printf("%ld X is eating\n", get_time() - philo->timestmp);
		mz_usleep(philo->t_eat);
		// if (get_time() - t > philo->t_die)
		// 	break ;
		printf("%ld X is sleeping\n", get_time() - philo->timestmp);
		mz_usleep(philo->t_sleep);
		// if (get_time() - t > philo->t_die)
		// 	break ;
		printf("%ld X is thinking\n", get_time() - philo->timestmp);
		mz_usleep(philo->t_sleep); // REMOVEEE
		// if (get_time() - t > philo->t_die)
		// 	break ;
	}
	printf("%ld X died\n", get_time() - philo->timestmp);
	return (NULL);
}
void *mz_routine2(void *data)
{
	t_philo	*philo;
	struct timeval 	time;
	time_t	t;
	
	philo = (t_philo *)data;
	while (1)
	{
		// t = get_time();
		printf("%ld X is sleeping\n", get_time() - philo->timestmp);
		mz_usleep(philo->t_sleep);
		// if (get_time() - t > philo->t_die)
		// 	break ;
		printf("%ld X is thinking\n", get_time() - philo->timestmp);
		mz_usleep(philo->t_sleep); // REMOVEEE
		// if (get_time() - t > philo->t_die)
		// 	break ;
		printf("%ld X has taken a fork\n", get_time() - philo->timestmp);
		// if (get_time() - t > philo->t_die)
		// 	break ;
		printf("%ld X is eating\n", get_time() - philo->timestmp);
		mz_usleep(philo->t_eat);
		// if (get_time() - t > philo->t_die)
		// 	break ;
	}
	printf("%ld X died\n", get_time() - philo->timestmp);
	return (NULL);
}
void *mz_routineMon(void *data)
{
	// t_philo	*philo;
	// struct timeval 	time;
	time_t	t;
	// time_t	x;
	// x = get_time();
	
	// philo = (t_philo *)data;
	while (1)
	{
		t = 1;
	// 	printf("%ld X has taken a fork\n", get_time() - x);
	// 	if (get_time() - t > philo->t_die)
	// 		break ;
	// 	printf("%ld X is eating\n", get_time() - x);
	// 	mz_usleep(philo->t_eat);
	// 	if (get_time() - t > philo->t_die)
	// 		break ;
	// 	printf("%ld X is sleeping\n", get_time() - x);
	// 	mz_usleep(philo->t_sleep);
	// 	if (get_time() - t > philo->t_die)
	// 		break ;
	// 	printf("%ld X is thinking\n", get_time() - x);
	// 	if (get_time() - t > philo->t_die)
	// 		break ;
	}
	
	// printf("%ld X died\n", get_time() - x);
	return (NULL);
}

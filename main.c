/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:03 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/07 14:39:40 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mz_init_philos(t_info *data)
{
	int i;
	
	data->philo = malloc(sizeof(t_philo *) * (data->n_philo + 2));
	i = 0;
	while (i <= data->n_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		data->philo[i]->id = i;
		if (i == data->n_philo)
			data->philo[i]->id = -1;
		data->philo[i]->meals_eaten = 0;
		data->philo[i]->fork_1 = data->fork[i];
		data->philo[i]->fork_2 = data->fork[(i + 1) % data->n_philo];
		data->philo[i]->data = data;
		i++;
	}
	data->philo[i] = NULL;
}

void	mz_init_forks(t_info *data)
{
	int i;

	data->fork = malloc(sizeof(t_fork *) * (data->n_philo + 1));
	i = 0;
	while (i < data->n_philo)
	{
		data->fork[i] = malloc(sizeof(t_fork));
		data->fork[i]->id = i;
		pthread_mutex_init(&data->fork[i]->fork, NULL);
		i++;
	}
	data->fork[i] = NULL;
}


int	mz_start(t_info *data)
{
	int i;


	i = 0;
	data->timestmp = get_time();
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i]->thread, NULL, mz_routine1, data->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->philo[i]->thread, NULL, mz_routineMon, data))
				return (1);
	return (0);
}

int main(int ac, char **av)
{
    t_info  		data;
	int				i;

    if (mz_parser(ac, av, &data) == 1)
        return (1);
	mz_init_forks(&data);
	mz_init_philos(&data);
	mz_start(&data);

	i = 0;
	while (i <= data.n_philo)
	{
		pthread_join(data.philo[i]->thread, NULL);
		i++;
	}
    return (0);
}
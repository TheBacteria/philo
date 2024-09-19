/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:03 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/19 13:01:32 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *mz_routine(void *allo)
{
	printf("FLEXXXXX !\n");
	sleep(2);
	return (NULL);
}

int main(int ac, char **av)
{
    t_info  		data;
	struct timeval 	time;
	pthread_t		*philo;
	int				i = 0;
	
    if (mz_parser(ac, av, &data) == 1)
        return (1);
	philo = malloc(data.n_philo * sizeof(pthread_t) + 1);
	philo[data.n_philo] = NULL;

	while (i < data.n_philo)
	{
		if (pthread_create(&philo[i], NULL, mz_routine, NULL))
			return (1);
		i++;
	}
	

	i = 0;
	while (i < data.n_philo)
	{
		if (pthread_join(philo[i], NULL))
			return (1);
		i++;
	}
	free(philo);


	// gettimeofday(&time, NULL);
	// printf("xx: %li\n", time.tv_sec * 1000 + time.tv_usec / 1000);
    // printf("XXXXXXXXXXXXXXXXXX\n");
    // printf("data->n_philo :%i\n", data.n_philo);
    // printf("data->t_die   :%i\n", data.t_die);
    // printf("data->t_eat   :%i\n", data.t_eat);
    // printf("data->t_sleep :%i\n", data.t_sleep);
    // printf("data->n_eat   :%i\n", data.n_eat);
    // printf("XXXXXXXXXXXXXXXXXX\n");
	
    return (0);
}





































    // printf("XXXXXXXXXXXXXXXXXX\n");
    // printf("data->n_philo :%i\n", data.n_philo);
    // printf("data->t_die   :%i\n", data.t_die);
    // printf("data->t_eat   :%i\n", data.t_eat);
    // printf("data->t_sleep :%i\n", data.t_sleep);
    // printf("data->n_eat   :%i\n", data.n_eat);
    // printf("XXXXXXXXXXXXXXXXXX\n");
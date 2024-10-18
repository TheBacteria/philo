/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:08:35 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/18 19:28:33 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mz_is_val(char *s)
{
	int				i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '\0')
		return (-1);
	while (s[i])
	{
		n = (n * 10) + s[i] - '0';
		if (s[i] < '0' || s[i] > '9' || n > 2147483647)
			return (-1);
		i++;
		while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		{
			i++;
			if (s[i] != 32 && (s[i] < 9 || s[i] > 13) && s[i] != '\0')
				return (-1);
		}
	}
	return ((int)n);
}

static int	mz_get_out(void)
{
	putstr_fd("Invalid arguments !\n", 2);
	putstr_fd("Usage: ", 2);
	putstr_fd("./philo number_of_philosophers time_to_die time_to_eat ", 2);
	putstr_fd("time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
	return (1);
}

static int	mz_parse_input(int ac, char **av, t_info *data)
{
	data->n_philo = mz_is_val(av[1]);
	data->t_die = mz_is_val(av[2]);
	data->t_eat = mz_is_val(av[3]);
	data->t_sleep = mz_is_val(av[4]);
	data->timestmp = get_time();
	data->is_dead = 0;
	data->is_full = 0;
	if (ac == 6)
		data->n_eat = mz_is_val(av[5]);
	else
		data->n_eat = -2;
	if (data->n_philo == -1 || data->t_die == -1 || data->t_eat == -1
		|| data->t_sleep == -1 || data->n_eat == -1)
		return (-1);
	if (data->n_philo == 0 || data->t_die == 0 || data->t_eat == 0
		|| data->t_sleep == 0 || data->n_eat == 0)
		return (-1);
	return (0);
}

int	mz_parser(int ac, char **av, t_info *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("gettimeofday function failed!\n");
		return (1);
	}
	if (ac != 5 && ac != 6)
		return (mz_get_out());
	if (mz_parse_input(ac, av, data) == -1)
		return (mz_get_out());
	if (pthread_mutex_init(&data->printer, NULL))
		return (mz_error_print(0));
	if (pthread_mutex_init(&data->death, NULL))
	{
		pthread_mutex_destroy(&data->printer);
		return (mz_error_print(0));
	}
	if (pthread_mutex_init(&data->full, NULL))
	{
		pthread_mutex_destroy(&data->printer);
		pthread_mutex_destroy(&data->death);
		return (mz_error_print(0));
	}
	return (0);
}

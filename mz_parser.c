/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:08:35 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/17 17:53:18 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mz_is_val(char *s)
{
	int				i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		n = (n * 10) + s[i] - '0';
		if (s[i] < '0' || s[i] > '9' || n > 2147483647)
			return (-1);
		i++;
	}
	return ((int)n);
}

static int	mz_get_out()
{
	putstr_fd("Invalid arguments !\n", 2);
	return (1);
}

static int	mz_parse_input(int ac, char **av, t_info *data)
{
	data->ac = ac;
	data->av = av;
	data->n_philo = mz_is_val(av[1]);
	data->t_die = mz_is_val(av[2]);
	data->t_eat = mz_is_val(av[3]);
	data->t_sleep = mz_is_val(av[4]);
	if (ac == 6)
		data->n_eat = mz_is_val(av[5]);
	else
		data->n_eat = -2;
	
	if (data->n_philo == -1 || data->t_die == -1 || data->t_eat == -1
		|| data->t_sleep == -1 || data->n_eat == -1)
		return(-1);
	return (0);
}

int	mz_parser(int ac, char **av, t_info  *data)
{
	if (ac != 5 && ac != 6)
		return(mz_get_out());
	if (mz_parse_input(ac, av, data) == -1)
		return(mz_get_out());
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_fail_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:37:30 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/15 15:45:30 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mz_fork_fail(t_info *data, int i, int n)
{
	if (n == 0)
		free(data->fork[i]);
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&data->fork[i]->fork);
		free(data->fork[i]);
	}
	free(data->fork);
	return(mz_error_print(n));
}

int	mz_free_forks(t_info *data, int n)
{
	int i;

	i = 0;
	while(data->fork[i])
	{
		pthread_mutex_destroy(&data->fork[i]->fork);
		free(data->fork[i]);
		i++;
	}
	free(data->fork);
	if (n > 0)
		return (mz_error_print(n));
	return (0);
}

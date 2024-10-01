/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:17:18 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/22 13:12:39 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	putstr_fd(char *msg, int fd)
{
	if (!msg)
		return ;
	while (*msg)
	{
		write(fd, msg, 1);
		msg++;
	}
}

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

time_t	get_timestamp(t_info *program)
{
	return (get_time() - program->timestmp);
}

int	mz_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	if (start == 0)
		return (-1);
	while ((get_time() - start) < ms)
	{
		usleep(500);
	}
	return (0);
}

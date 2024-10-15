/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:17:18 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/15 15:27:14 by mzouine          ###   ########.fr       */
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

int	mz_usleep(t_philo *philo, size_t ms)
{
	size_t	start;

	start = get_time();
	if (start == 0)
		return (1);
	while ((get_time() - start) < ms)
	{
		usleep(500);
		if (mz_check_death2(philo))
			break ;
	}
	return (0);
}

int	mz_error_print(int n)
{
	if (n == 0)
		printf("Mutex initialisation error !\n");
	else if(n == 1)
		printf("Malloc failed!\n");
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:03 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/17 17:54:08 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_info  data;

    if (mz_parser(ac, av, &data) == 1)
        return (1);
    
    return (0);
}





































    // printf("XXXXXXXXXXXXXXXXXX\n");
    // printf("data->n_philo :%i\n", data.n_philo);
    // printf("data->t_die   :%i\n", data.t_die);
    // printf("data->t_eat   :%i\n", data.t_eat);
    // printf("data->t_sleep :%i\n", data.t_sleep);
    // printf("data->n_eat   :%i\n", data.n_eat);
    // printf("XXXXXXXXXXXXXXXXXX\n");
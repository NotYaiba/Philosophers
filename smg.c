/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 02:27:29 by yaiba             #+#    #+#             */
/*   Updated: 2021/10/19 02:36:14 by yaiba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_errors(int ac, char **av)
{
	if (ac < 5 || ac > 6 || check_args(av) == 0)
		return (log_error("Error.\n", 1));
	if (ft_atoi(av[1]) == 0)
        return (1);
    if ((av[5]))
    {
        if (ft_atoi(av[5]) == 0)
            return (1);
    }
    return (0);

}
	
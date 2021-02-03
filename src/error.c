/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:46:03 by vserra            #+#    #+#             */
/*   Updated: 2021/02/03 13:13:45 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	quit(t_parsing *parse)
// {
// 	exit(EXIT_FAILURE);
// }

int print_error(t_parsing *parse, int error)
{
	(void)parse;
	ft_putstr_fd(g_str_error[error], 2);
	exit(EXIT_FAILURE);
}

// print_error(parse, RESOLUTION);

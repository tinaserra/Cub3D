/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:46:03 by vserra            #+#    #+#             */
/*   Updated: 2020/10/24 11:17:56 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ft_putstr_fd("Error :\n[F] Wrong caracter at the end\n", 2);

// void	quit(t_parsing *parse)
// {
// 	exit(EXIT_FAILURE);
// }

void	print_error(t_parsing *parse, int error)
{
	(void)parse;
	if (error == CUB_DIR)
		ft_putstr_fd("Error :\n[OPEN] The argument .cub is a directory\n", 2);
	if (error == CUB_INVALIDE)
		ft_putstr_fd("Error :\n[OPEN] The argument .cub dosn't exist or is invalide\n", 2);
	if (error == RESOLUTION)
		ft_putstr_fd("Error :\n[R] Wrong resolution or not specified\n", 2);
	if (error == RESOLUTION_END)
		ft_putstr_fd("Error :\n[R] Wrong caracter at the end\n", 2);
	if (error == F_COLOR)
		ft_putstr_fd("Error :\n[F] Wrong color or not specified\n", 2);
	if (error == F_COLOR_END)
		ft_putstr_fd("Error :\n[F] Wrong caracter at the end\n", 2);
	if (error == C_COLOR)
		ft_putstr_fd("Error :\n[C] Wrong color or not specified\n", 2);
	if (error == C_COLOR_END)
		ft_putstr_fd("Error :\n[C] Wrong caracter at the end\n", 2);
	exit(EXIT_FAILURE);
	// quit(parse);
}

// print_error(parse, RESOLUTION);

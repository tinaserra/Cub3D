/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:46:03 by vserra            #+#    #+#             */
/*   Updated: 2020/11/02 14:41:51 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ft_putstr_fd("Error :\n[F] Wrong caracter at the end\n", 2);

// void	quit(t_parsing *parse)
// {
// 	exit(EXIT_FAILURE);
// }

void	free_error(t_parsing *parse, int error)
{
	if (parse->map != NULL)
		free(parse->map);
	if (error == MALLOC_FAILED)
		ft_putstr_fd("Error :\n[Failed] memory allocation in get_map\n", 2);
}

void	print_error(t_parsing *parse, int error)
{
	(void)parse;
	if (error == FILE_NAME)
		ft_putstr_fd("Error :\n[FILE] Ivalide name or extention\n", 1);
	if (error == CUB_DIR)
		ft_putstr_fd("Error :\n[OPEN] The argument .cub is a directory\n", 2);
	if (error == CUB_INVALIDE)
		ft_putstr_fd("Error :\n[OPEN] The argument .cub dosn't exist or is invalide\n", 2);
	if (error == RESOLUTION)
		ft_putstr_fd("Error :\n[R] Wrong resolution or not specified\n", 2);
	if (error == RESOLUTION_END)
		ft_putstr_fd("Error :\n[R] Wrong caracter\n", 2);
	if (error == F_COLOR)
		ft_putstr_fd("Error :\n[F] Wrong color or not specified\n", 2);
	if (error == F_COLOR_END)
		ft_putstr_fd("Error :\n[F] Wrong caracter\n", 2);
	if (error == C_COLOR)
		ft_putstr_fd("Error :\n[C] Wrong color or not specified\n", 2);
	if (error == C_COLOR_END)
		ft_putstr_fd("Error :\n[C] Wrong caracter\n", 2);
	if (error == MORE_NUM)
		ft_putstr_fd("Error :\n[INT] More numbers than expected\n", 2);
	if (error == DOUBLE_ELEMENT)
		ft_putstr_fd("Error :\n[ELEMENT] in double\n", 2);
	if (error == MAP_CHAR_AFTER)
		ft_putstr_fd("Error :\n[MAP] Wrong caracter after the map\n", 2);
	if (error == NO_MAP)
		ft_putstr_fd("Error :\n[MAP] No map in file\n", 2);
	if (error == MULTI_PLAYER)
		ft_putstr_fd("Error :\n[MAP] More than 1 player\n", 2);
	exit(EXIT_FAILURE);
	// quit(parse);
}

// print_error(parse, RESOLUTION);

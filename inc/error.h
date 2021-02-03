/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:11:16 by vserra            #+#    #+#             */
/*   Updated: 2021/02/03 13:10:31 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* Errors */

typedef enum	e_error{
	FILE_NAME,
	CUB_DIR,
	CUB_INVALIDE,
	RESOLUTION,
	RESOLUTION_END,
	F_COLOR,
	F_COLOR_END,
	C_COLOR,
	C_COLOR_END,
	MORE_NUM,
	DOUBLE_ELEMENT,
	MAP_WRONG_CHAR,
	MAP_CHAR_AFTER,
	NO_MAP,
	MULTI_PLAYER,
	NO_PLAYER,
	MAP_WALL,
	MAP_INCOMPLETE,
	MLX_INIT,
	NEW_WINDOW,
	NEW_IMAGE,

	MALLOC_FAILED,
	NUMBER
}				t_error;

static char g_str_error[NUMBER][256] =
{
	[FILE_NAME] = "Error :\n[FILE] Ivalide name or extention\n",
	[CUB_DIR] = "Error :\n[FILE] The argument .cub is a directory\n",
	[CUB_INVALIDE] = "Error :\n[FILE] The argument .cub dosn't exist or is invalide\n",
	[RESOLUTION] = "Error :\n[R] Wrong resolution or not specified\n",
	[RESOLUTION_END] = "Error :\n[R] Wrong caracter\n",
	[F_COLOR] = "Error :\n[F] Wrong color or not specified\n",
	[F_COLOR_END] = "Error :\n[F] Wrong caracter\n",
	[C_COLOR] = "Error :\n[C] Wrong color or not specified\n",
	[C_COLOR_END]= "Error :\n[C] Wrong caracter\n",
	[MORE_NUM] = "Error :\n[INT] More numbers than expected\n",
	[DOUBLE_ELEMENT] = "Error :\n[ELEMENT] in double\n",
	[MAP_WRONG_CHAR] = "Error :\n[MAP] Wrong char in map\n",
	[MAP_CHAR_AFTER] = "Error :\n[MAP] Wrong caracter after the map\n",
	[NO_MAP] = "Error :\n[MAP] No map in file\n",
	[MULTI_PLAYER] = "Error :\n[MAP] More than 1 player\n",
	[NO_PLAYER] = "Error :\n[MAP] Miss a player\n",
	[MAP_WALL] = "Error :\n[MAP] Not close\n",
	[MAP_INCOMPLETE] = "Error :\n[MAP] incomplete\n",
	[MLX_INIT] = "Error :\n[MLX] Init mlx\n",
	[NEW_WINDOW] = "Error :\n[MLX] Create new window\n",
	[NEW_IMAGE] = "Error :\n[MLX] Create new image\n",

	[MALLOC_FAILED] = "Error :\n[Failed] memory allocation in get_map\n"
};

#endif
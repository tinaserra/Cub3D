/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:11:16 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:49:05 by vserra           ###   ########.fr       */
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
	DOUBLE_RESOLUTION,
	DOUBLE_COLOR,
	EMPTY_NO,
	EMPTY_WE,
	EMPTY_SO,
	EMPTY_EA,
	EMPTY_S,
	DOUBLE_NO,
	DOUBLE_WE,
	DOUBLE_SO,
	DOUBLE_EA,
	DOUBLE_S,
	WRONG_NO,
	WRONG_WE,
	WRONG_SO,
	WRONG_EA,
	WRONG_S,
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
	[DOUBLE_RESOLUTION] = "Error :\n[R] in double\n",
	[DOUBLE_COLOR] = "Error :\n[COLOR] in double\n",
	[EMPTY_NO] = "Error :\n[NO] is not specified\n",
	[EMPTY_WE] = "Error :\n[WE] is not specified\n",
	[EMPTY_SO] = "Error :\n[SO] is not specified\n",
	[EMPTY_EA] = "Error :\n[EA] is not specified\n",
	[EMPTY_S] = "Error :\n[S] is not specified\n",
	[DOUBLE_NO] = "Error :\n[NO] in double\n",
	[DOUBLE_WE] = "Error :\n[WE] in double\n",
	[DOUBLE_SO] = "Error :\n[SO] in double\n",
	[DOUBLE_EA] = "Error :\n[EA] in double\n",
	[DOUBLE_S] = "Error :\n[S] in double\n",
	[WRONG_NO] = "Error :\n[NO] Wrong path\n",
	[WRONG_WE] = "Error :\n[WE] Wrong path\n",
	[WRONG_SO] = "Error :\n[SO] Wrong path\n",
	[WRONG_EA] = "Error :\n[EA] Wrong path\n",
	[WRONG_S] = "Error :\n[S] Wrong path\n",
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 10:42:07 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** On check d'abord la première et la derniere colonne,
** puis la première et la derniere ligne.
*/

static void	check_borders(t_env *env)
{
	int i;

	i = 0;
	while (i < env->map.nb_lines)
	{
		if (env->map.map[i][0] != '1' && env->map.map[i][0] != '.')
			print_error(env, MAP_WALL);
		if (env->map.map[i][env->map.len_line - 1] != '1'
			&& env->map.map[i][env->map.len_line - 1] != '.')
			print_error(env, MAP_WALL);
		i++;
	}
	i = 0;
	while (i < env->map.len_line)
	{
		if (env->map.map[0][i] != '1' && env->map.map[0][i] != '.')
			print_error(env, MAP_WALL);
		if (env->map.map[env->map.nb_lines - 1][i] != '1'
			&& env->map.map[env->map.nb_lines - 1][i] != '.')
			print_error(env, MAP_WALL);
		i++;
	}
}

/*
** On check d'abord la ligne du dessus, puis la ligne ou l'on se trouve,
** enfin la ligne du dessous.
*/

static void	check_spaces(t_env *env, int x, int y)
{
	if (y != 0 && x != 0 && env->map.map[y - 1][x - 1] == '.')
		print_error(env, MAP_WALL);
	if (y != 0 && env->map.map[y - 1][x] == '.')
		print_error(env, MAP_WALL);
	if (y != 0 && x != env->map.len_line && env->map.map[y - 1][x + 1] == '.')
		print_error(env, MAP_WALL);
	if (x != 0 && env->map.map[y][x - 1] == '.')
		print_error(env, MAP_WALL);
	if (x != env->map.len_line && env->map.map[y][x + 1] == '.')
		print_error(env, MAP_WALL);
	if (y != env->map.len_line && x != 0 && env->map.map[y + 1][x - 1] == '.')
		print_error(env, MAP_WALL);
	if (y != env->map.len_line && env->map.map[y + 1][x] == '.')
		print_error(env, MAP_WALL);
	if (y != env->map.len_line && x != env->map.len_line
		&& env->map.map[y + 1][x + 1] == '.')
		print_error(env, MAP_WALL);
}

void		check_walls(t_env *env)
{
	int x;
	int y;

	check_borders(env);
	y = 0;
	while (y < env->map.nb_lines)
	{
		x = 0;
		while (x < env->map.len_line)
		{
			if (env->map.map[y][x] == '0' || env->map.map[y][x] == '2')
				check_spaces(env, x, y);
			x++;
		}
		y++;
	}
}

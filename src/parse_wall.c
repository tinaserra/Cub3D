/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:54:33 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_borders(t_env *env)
{
	int x;
	int y;
	y = 0;
	x = 0;
	// first colonne & last colonne
	while (y < env->map.nb_lines)
	{
		if (env->map.map[y][0] != '1' && env->map.map[y][0] != '.')
			print_error(env, MAP_WALL);
		if (env->map.map[y][env->map.len_line - 1] != '1'
			&& env->map.map[y][env->map.len_line - 1] != '.')
			print_error(env, MAP_WALL);
		y++;
	}
	// first line & last line
	while (x < env->map.len_line)
	{
		if (env->map.map[0][x] != '1' && env->map.map[0][x] != '.')
			print_error(env, MAP_WALL);
		if (env->map.map[env->map.nb_lines - 1][x] != '1'
			&& env->map.map[env->map.nb_lines - 1][x] != '.')
			print_error(env, MAP_WALL);
		x++;
	}
}

void	check_spaces(t_env *env, int x, int y)
{
	// ligne au dessus
	if (y != 0 && x != 0 && env->map.map[y - 1][x - 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
	if (y != 0 && env->map.map[y - 1][x] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
	if (y != 0 && x != env->map.len_line && env->map.map[y - 1][x + 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
	// return ;

	// ligne
	if (x != 0 && env->map.map[y][x - 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
	if (x != env->map.len_line && env->map.map[y][x + 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}

	// ligne en dessous
	if (y != env->map.len_line && x != 0 && env->map.map[y + 1][x - 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
	if (y != env->map.len_line && env->map.map[y + 1][x] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
	if (y != env->map.len_line && x != env->map.len_line
		&& env->map.map[y + 1][x + 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(env, MAP_WALL);
	}
}

void	check_walls(t_env *env)
{
	int x;
	int y;

	y = 0;
	debug_print_map(env);
	while (y < env->map.nb_lines)
	{
		x = 0;
		while (x < env->map.len_line) // env->map.map.nb_lines
		{
			if (env->map.map[y][x] == '0' || env->map.map[y][x] == '2')
			{
				check_spaces(env, x, y);
			}
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:42:56 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 10:58:09 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** env->ply.px	-> [+0,5] Pour se positioner au centre de la case
** player.dirx		-> commence à -1 pour N, 1 pour S, 0 sinon
** player.diry		-> commence à -1 pour W, 1 pour E, 0 sinon
*/

static int	player_position(t_env *env, char c, int i, int j)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (env->ply.orient_start == 'o')
		{
			env->ply.orient_start = c;
			env->ply.px = i + 0.5;
			env->ply.py = j + 0.5;
			if (c == 'N')
				env->ply.dirx = -1;
			if (c == 'E')
				env->ply.diry = 1;
			if (c == 'S')
				env->ply.dirx = 1;
			if (c == 'W')
				env->ply.diry = -1;
			return (0);
		}
		else
			print_error(env, MULTI_PLAYER);
	}
	return (-1);
}

int			dup_map(char *str, t_env *env)
{
	static int	y = 0;
	int			x;

	x = 0;
	env->map.map[y] = NULL;
	if (!(env->map.map[y] = malloc(sizeof(char) * env->map.len_line + 1)))
		print_error(env, MALLOC_FAILED);
	while (str[x] != '\0')
	{
		if (player_position(env, str[x], y, x) == 0)
			env->map.map[y][x] = '0';
		else if (str[x] == ' ')
			env->map.map[y][x] = '.';
		else
			env->map.map[y][x] = str[x];
		x++;
	}
	while (x < env->map.len_line)
	{
		env->map.map[y][x] = '.';
		x++;
	}
	env->map.map[y][x] = '\0';
	y++;
	return (0);
}

int			is_a_map(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '0' 
			&& str[i] != '2' && str[i] != 'N' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'W' && str[i])
			return (-1);
		i++;
	}
	return (0);
}

int			is_char_map(char *str, t_env *env)
{
	while (str[env->i])
	{
		if (str[env->i] != '1' && str[env->i] != ' ' && str[env->i] != '0'
			&& str[env->i] != '2' && str[env->i] != 'N' && str[env->i] != 'S'
			&& str[env->i] != 'E' && str[env->i] != 'W' && str[env->i])
			{
				print_error(env, MAP_WRONG_CHAR);
			}
		env->i++;
	}
	return (0);
}

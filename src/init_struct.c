/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2021/02/19 16:44:52 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse(t_env *env)
{
	*env = (t_env) {
	.res.x = -1,
	.res.y = -1,
	.map.nb_lines = -1,
	.map.len_line = -1,
	.col.red_f = -1,
	.col.green_f = -1,
	.col.blue_f = -1,
	.col.red_c = -1,
	.col.green_c = -1,
	.col.blue_c = -1,
	.player.orient_start = 'o',
	};
}

/*
** printf("R = %d\n", parse->col.red_f);
** printf("G = %d\n", parse->col.green_f);
** printf("B = %d\n", parse->col.blue_f);
** printf("R = %d\n", parse->col.red_c);
** printf("G = %d\n", parse->col.green_c);
** printf("B = %d\n", parse->col.blue_c);
*/

void	init_texture(t_env *env)
{
	if (env->wall.side == 0 && env->raydir.x < 0)
		env->tex.dir = NO;
	if (env->wall.side == 1 && env->raydir.y < 0)
		env->tex.dir = WE;
	if (env->wall.side == 0 && env->raydir.x >= 0)
		env->tex.dir = SO;
	if (env->wall.side == 1 && env->raydir.y >= 0)
		env->tex.dir = EA;

	// // calculer la valeur de wallx, où exactement le mur a été touché
	// if (env->wall.side == 0)
	// 	env->tex.wallx = env->player.py + env->wall.pdist * env->raydir.y;
	// else
	// 	env->tex.wallx = env->player.px + env->wall.pdist * env->raydir.x;
	// env->tex.wallx -= floor((env->tex.wallx)); // calcule l'arrondi entier inférieur de la valeur spécifiée en paramètre
}

void	init_start_mlx(t_env *env)
{
	if (env->player.orient_start == 'N')
		env->plane.y = 0.66;
	if (env->player.orient_start == 'S')
		env->plane.y = -0.66;
	if (env->player.orient_start == 'E')
		env->plane.x = 0.66;
	if (env->player.orient_start == 'W')
		env->plane.x = -0.66;
}

void	init_env(t_env *env)
{
	env->camerax = 2 * env->x / (double)env->res.x - 1;
	env->raydir.x = env->player.dirx + env->plane.x * env->camerax;
	env->raydir.y = env->player.diry + env->plane.y * env->camerax;
	env->map.x = (int)env->player.px;
	env->map.y = (int)env->player.py;
	env->deltadist.x = fabs(1 / env->raydir.x);
	env->deltadist.y = fabs(1 / env->raydir.y);
	env->wall.hit = 0;
}

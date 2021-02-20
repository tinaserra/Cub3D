/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 11:00:22 by vserra           ###   ########.fr       */
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
	.ply.orient_start = 'o',
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

void	init_start_mlx(t_env *env)
{
	if (env->ply.orient_start == 'N')
		env->plane.y = 0.66;
	if (env->ply.orient_start == 'S')
		env->plane.y = -0.66;
	if (env->ply.orient_start == 'E')
		env->plane.x = 0.66;
	if (env->ply.orient_start == 'W')
		env->plane.x = -0.66;
}

void	init_env(t_env *env)
{
	env->camerax = 2 * env->x / (double)env->res.x - 1;
	env->raydir.x = env->ply.dirx + env->plane.x * env->camerax;
	env->raydir.y = env->ply.diry + env->plane.y * env->camerax;
	env->map.x = (int)env->ply.px;
	env->map.y = (int)env->ply.py;
	env->deltadist.x = fabs(1 / env->raydir.x);
	env->deltadist.y = fabs(1 / env->raydir.y);
	env->hit = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2021/03/22 14:04:26 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse(t_env *env)
{
	*env = (t_env) {
	.res.x = -1,
	.res.y = -1,
	.map.len_line = -1,
	.f.red = -1,
	.f.green = -1,
	.f.blue = -1,
	.c.red = -1,
	.c.green = -1,
	.c.blue = -1,
	.ply.orient_start = 'o',
	};
}

/*
** mspeed -> la valeur constante est en carrés / seconde
** rspeed -> la valeur constante est en radians / seconde
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
	if (!(env->zbuffer = malloc(sizeof(double) * env->res.x)))
		print_error(env, MALLOC_FAILED);
}

void	init_env(t_env *env)
{
	env->camerax = 2 * env->x / (double)env->res.x - 1;
	env->raydir.x = env->ply.dirx + env->plane.x * env->camerax;
	env->raydir.y = env->ply.diry + env->plane.y * env->camerax;
	env->map.x = (int)env->ply.x;
	env->map.y = (int)env->ply.y;
	env->deltadist.x = fabs(1 / env->raydir.x);
	env->deltadist.y = fabs(1 / env->raydir.y);
	env->hit = 0;
}

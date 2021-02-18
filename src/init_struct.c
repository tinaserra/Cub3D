/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:41:28 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse(t_env *env)
{
	*env = (t_env) {
	.save = 0,
	.res.x = -1,
	.res.y = -1,
	.map.nb_lines = -1,
	.map.len_line = -1,
	.map.end_map = 0,
	.col.red_f = -1,
	.col.green_f = -1,
	.col.blue_f = -1,
	.col.red_c = -1,
	.col.green_c = -1,
	.col.blue_c = -1,
	.map.map = NULL,
	.player.orient_start = 'o',
	.player.dirx = 0,
	.player.diry = 0,
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

// void	init_env(t_env *env)
// {
// 	*env = (t_env) {
// 	// calculer la position et la direction
// 	.camerax = 2 * env->x / (double)env->res.x - 1, // coordonnée x dans l'espace caméra
// 	.raydir.x = env->player.dirx + env->plane.x * env->camerax,
// 	.raydir.y = env->player.diry + env->plane.y * env->camerax,
// 	// dans quel carré de la carte nous nous trouvons
// 	.map.x = (int)env->player.px,
// 	.map.y = (int)env->player.py,
// 	// longueur du rayon d'un côté x ou y au coté x ou y
// 	.deltadist.x = fabs (1 / env->raydir.x), //= sqrt(1 + (env->raydir.y * env->raydir.y) / (env->raydir.x * env->raydir.x));
// 	.deltadist.y = fabs (1 / env->raydir.y), //= sqrt(1 + (env->raydir.x * env->raydir.x) / (env->raydir.y * env->raydir.y));
// 	.wall.hit = 0, // y a-t-il eu un mur touché?
// 	};
// 	ft_putstr_fd("YOHANN EST UN GROS PD 2\n", 1);
// }

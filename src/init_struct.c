/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2021/02/17 19:47:37 by vserra           ###   ########.fr       */
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
** parse->col.red_f = -1;
** parse->col.green_f = -1;
** parse->col.blue_f = -1;
**
** parse->col.red_c = -1;
** parse->col.green_c = -1;
** parse->col.blue_c = -1;
**
** parse->resx = -1;
** parse->resy = -1;
**
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
		env->planey = 0.66;
	if (env->player.orient_start == 'S')
		env->planey = -0.66;
	if (env->player.orient_start == 'E')
		env->planex = 0.66;
	if (env->player.orient_start == 'W')
		env->planex = -0.66;
}

void	init_env(t_env *env)
{
	env->camerax = 2 * env->x / (double)env->res.x - 1;
	env->raydirx = env->player.dirx + env->planex * env->camerax;
	env->raydiry = env->player.diry + env->planey * env->camerax;
	env->map.x = (int)env->player.px;
	env->map.y = (int)env->player.py;
	env->deltadistx = fabs (1 / env->raydirx);
	env->deltadisty = fabs (1 / env->raydiry);
	env->hit = 0;
}

// void	init_env(t_env *env)
// {
// 	*env = (t_env) {
// 	// calculer la position et la direction
// 	.camerax = 2 * env->x / (double)env->res.x - 1, // coordonnée x dans l'espace caméra
// 	.raydirx = env->player.dirx + env->planex * env->camerax,
// 	.raydiry = env->player.diry + env->planey * env->camerax,
// 	// dans quel carré de la carte nous nous trouvons
// 	.map.x = (int)env->player.px,
// 	.map.y = (int)env->player.py,
// 	// longueur du rayon d'un côté x ou y au coté x ou y
// 	.deltadistx = fabs (1 / env->raydirx), //= sqrt(1 + (env->raydiry * env->raydiry) / (env->raydirx * env->raydirx));
// 	.deltadisty = fabs (1 / env->raydiry), //= sqrt(1 + (env->raydirx * env->raydirx) / (env->raydiry * env->raydiry));
// 	.hit = 0, // y a-t-il eu un mur touché?
// 	};
// 	ft_putstr_fd("YOHANN EST UN GROS PD 2\n", 1);
// }

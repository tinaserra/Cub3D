/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2021/02/03 10:39:58 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse(t_parsing *parse)
{
	*parse = (t_parsing) {
	.save = 0,
	.resx = -1,
	.resy = -1,
	.nb_lines = -1,
	.len_line = -1,
	.end_map = 0,
	.no = -1,
	.ea = -1,
	.so = -1,
	.we = -1,
	.col.red_f = -1,
	.col.green_f = -1,
	.col.blue_f = -1,
	.col.red_c = -1,
	.col.green_c = -1,
	.col.blue_c = -1,
	.map = NULL,
	.player.px = 'o',
	.player.dirX = 0,
	.player.dirY = 0,
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

void	init_env(t_env *env)
{
	env->cameraX = 2 * env->x / (double)env->parse.resx - 1;
	env->rayDirX = env->parse.player.dirX + env->planeX * env->cameraX;
	env->rayDirY = env->parse.player.dirY + env->planeY * env->cameraX;
	env->mapX = (int)env->parse.player.px;
	env->mapY = (int)env->parse.player.py;
	env->deltaDistX = fabs (1 / env->rayDirX);
	env->deltaDistY = fabs (1 / env->rayDirY);
	env->hit = 0;
}

// void	init_env(t_env *env)
// {
// 	*env = (t_env) {
// 	// calculer la position et la direction
// 	.cameraX = 2 * env->x / (double)env->parse.resx - 1, // coordonnée x dans l'espace caméra
// 	.rayDirX = env->parse.player.dirX + env->planeX * env->cameraX,
// 	.rayDirY = env->parse.player.dirY + env->planeY * env->cameraX,
// 	// dans quel carré de la carte nous nous trouvons
// 	.mapX = (int)env->parse.player.px,
// 	.mapY = (int)env->parse.player.py,
// 	// longueur du rayon d'un côté x ou y au coté x ou y
// 	.deltaDistX = fabs (1 / env->rayDirX), //= sqrt(1 + (env->rayDirY * env->rayDirY) / (env->rayDirX * env->rayDirX));
// 	.deltaDistY = fabs (1 / env->rayDirY), //= sqrt(1 + (env->rayDirX * env->rayDirX) / (env->rayDirY * env->rayDirY));
// 	.hit = 0, // y a-t-il eu un mur touché?
// 	};
// 	ft_putstr_fd("YOHANN EST UN GROS PD 2\n", 1);
// }

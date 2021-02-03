/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/02/03 10:59:55 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->parse.map[(int)(env->parse.player.px + env->parse.player.dirX /** env->moveSpeed*/)][(int)(env->parse.player.py)] == '0')
		env->parse.player.px += env->parse.player.dirX /** env->moveSpeed*/;
	if (env->parse.map[(int)(env->parse.player.px)][(int)(env->parse.player.py + env->parse.player.dirY /** env->moveSpeed)*/)] == '0')
		env->parse.player.py += env->parse.player.dirY /** env->moveSpeed*/;
}

void	go_back(t_env *env)
{
	if (env->parse.map[(int)(env->parse.player.px - env->parse.player.dirX /** env->moveSpeed*/)][(int)(env->parse.player.py)] == '0')
		env->parse.player.px -= env->parse.player.dirX /** env->moveSpeed*/;
	if (env->parse.map[(int)(env->parse.player.px)][(int)(env->parse.player.py - env->parse.player.dirY /** env->moveSpeed*/)] == '0')
		env->parse.player.py -= env->parse.player.dirY /** env->moveSpeed*/;
}

void	go_left(t_env *env)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = env->parse.player.dirX;
	oldPlaneX = env->planeX;

	// La direction de la caméra et le plan de la caméra doivent être tournés
	env->parse.player.dirX = env->parse.player.dirX * cos(env->rotSpeed) - env->parse.player.dirY * sin(env->rotSpeed);
	env->parse.player.dirY = oldDirX * sin(env->rotSpeed) + env->parse.player.dirY * cos(env->rotSpeed);
	env->planeX = env->planeX * cos(env->rotSpeed) - env->planeY * sin(env->rotSpeed);
	env->planeY = oldPlaneX * sin(env->rotSpeed) + env->planeY * cos(env->rotSpeed);
}

void	go_right(t_env *env)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = env->parse.player.dirX;
	oldPlaneX = env->planeX;

	// La direction de la caméra et le plan de la caméra doivent être tournés
	env->parse.player.dirX = env->parse.player.dirX * cos(-env->rotSpeed) - env->parse.player.dirY * sin(-env->rotSpeed);
	env->parse.player.dirY = oldDirX * sin(-env->rotSpeed) + env->parse.player.dirY * cos(-env->rotSpeed);
	env->planeX = env->planeX * cos(-env->rotSpeed) - env->planeY * sin(-env->rotSpeed);
	env->planeY = oldPlaneX * sin(-env->rotSpeed) + env->planeY * cos(-env->rotSpeed);
}
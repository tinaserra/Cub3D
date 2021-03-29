/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:14:27 by vserra            #+#    #+#             */
/*   Updated: 2021/03/22 14:08:04 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** La direction de la caméra et le plan de la caméra doivent être tournés
*/

static void	turn_left(t_env *env)
{
	double olddirx;
	double oldplanex;

	olddirx = env->ply.dirx;
	oldplanex = env->plane.x;
	env->ply.dirx = env->ply.dirx * cos(RSPEED) - env->ply.diry * sin(RSPEED);
	env->ply.diry = olddirx * sin(RSPEED) + env->ply.diry * cos(RSPEED);
	env->plane.x = env->plane.x * cos(RSPEED) - env->plane.y * sin(RSPEED);
	env->plane.y = oldplanex * sin(RSPEED) + env->plane.y * cos(RSPEED);
}

static void	turn_right(t_env *env)
{
	double olddirx;
	double oldplanex;

	olddirx = env->ply.dirx;
	oldplanex = env->plane.x;
	env->ply.dirx = env->ply.dirx * cos(-RSPEED) - env->ply.diry * sin(-RSPEED);
	env->ply.diry = olddirx * sin(-RSPEED) + env->ply.diry * cos(-RSPEED);
	env->plane.x = env->plane.x * cos(-RSPEED) - env->plane.y * sin(-RSPEED);
	env->plane.y = oldplanex * sin(-RSPEED) + env->plane.y * cos(-RSPEED);
}

void		keys_control(t_env *env)
{
	if (env->keyboard[KEY_ESCAPE])
		ft_quit(env);
	if (env->keyboard[KEY_W])
		go_straight(env);
	if (env->keyboard[KEY_S])
		go_back(env);
	if (env->keyboard[KEY_D])
		go_right(env);
	if (env->keyboard[KEY_A])
		go_left(env);
	if (env->keyboard[KEY_RIGHT])
		turn_right(env);
	if (env->keyboard[KEY_LEFT])
		turn_left(env);
}

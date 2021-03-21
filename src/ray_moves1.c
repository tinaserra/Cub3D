/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:14:27 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 19:16:58 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_quit(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img.image);
	mlx_destroy_window(env->mlx, env->window);
	exit(0);
}

/*
** La direction de la caméra et le plan de la caméra doivent être tournés
*/

static void	turn_left(t_env *env)
{
	double olddirx;
	double oldplanex;

	olddirx = env->ply.dirx;
	oldplanex = env->plane.x;
	env->ply.dirx = env->ply.dirx * cos(env->ply.rspeed)
					- env->ply.diry * sin(env->ply.rspeed);
	env->ply.diry = olddirx * sin(env->ply.rspeed) + env->ply.diry
					* cos(env->ply.rspeed);
	env->plane.x = env->plane.x * cos(env->ply.rspeed)
					- env->plane.y * sin(env->ply.rspeed);
	env->plane.y = oldplanex * sin(env->ply.rspeed)
					+ env->plane.y * cos(env->ply.rspeed);
}

static void	turn_right(t_env *env)
{
	double olddirx;
	double oldplanex;

	olddirx = env->ply.dirx;
	oldplanex = env->plane.x;
	env->ply.dirx = env->ply.dirx * cos(-env->ply.rspeed)
					- env->ply.diry * sin(-env->ply.rspeed);
	env->ply.diry = olddirx * sin(-env->ply.rspeed)
					+ env->ply.diry * cos(-env->ply.rspeed);
	env->plane.x = env->plane.x * cos(-env->ply.rspeed)
					- env->plane.y * sin(-env->ply.rspeed);
	env->plane.y = oldplanex * sin(-env->ply.rspeed)
					+ env->plane.y * cos(-env->ply.rspeed);
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

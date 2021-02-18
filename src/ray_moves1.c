/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:14:27 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:27:39 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_quit(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img.image);
	mlx_destroy_window(env->mlx, env->window);
	exit(0);
}

void	turn_left(t_env *env)
{
	double olddirx;
	double oldplanex;

	olddirx = env->player.dirx;
	oldplanex = env->plane.x;

	// La direction de la caméra et le plan de la caméra doivent être tournés
	env->player.dirx = env->player.dirx * cos(env->player.rspeed) - env->player.diry * sin(env->player.rspeed);
	env->player.diry = olddirx * sin(env->player.rspeed) + env->player.diry * cos(env->player.rspeed);
	env->plane.x = env->plane.x * cos(env->player.rspeed) - env->plane.y * sin(env->player.rspeed);
	env->plane.y = oldplanex * sin(env->player.rspeed) + env->plane.y * cos(env->player.rspeed);
}

void	turn_right(t_env *env)
{
	double olddirx;
	double oldplanex;

	olddirx = env->player.dirx;
	oldplanex = env->plane.x;

	// La direction de la caméra et le plan de la caméra doivent être tournés
	env->player.dirx = env->player.dirx * cos(-env->player.rspeed) - env->player.diry * sin(-env->player.rspeed);
	env->player.diry = olddirx * sin(-env->player.rspeed) + env->player.diry * cos(-env->player.rspeed);
	env->plane.x = env->plane.x * cos(-env->player.rspeed) - env->plane.y * sin(-env->player.rspeed);
	env->plane.y = oldplanex * sin(-env->player.rspeed) + env->plane.y * cos(-env->player.rspeed);
}

void	keys_control(t_env *env)
{
	if (env->keyboard[KEY_ESCAPE])
		ft_quit(env);
	if (env->keyboard[KEY_W]) // avance si pas de mur devant toi
		go_straight(env);
	if (env->keyboard[KEY_S]) // recule si aucun mur derrière vous
		go_back(env);
	if (env->keyboard[KEY_D]) // deplacement vers la droite
		go_right(env);
	if (env->keyboard[KEY_A]) // deplacement vers la gauche
		go_left(env);
	if (env->keyboard[KEY_RIGHT]) // deplacement vers la droite
		turn_right(env);
	if (env->keyboard[KEY_LEFT]) // deplacement vers la gauche
		turn_left(env);
}

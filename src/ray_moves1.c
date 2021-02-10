/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:14:27 by vserra            #+#    #+#             */
/*   Updated: 2021/02/10 13:27:26 by vserra           ###   ########.fr       */
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

void	turn_right(t_env *env)
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
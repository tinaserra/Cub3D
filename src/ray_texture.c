/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:21:53 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 19:59:31 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_texdir(t_env *env)
{
	if (env->side == 0 && env->raydir.x < 0)
		env->tex.dir = NO;
	if (env->side == 1 && env->raydir.y < 0)
		env->tex.dir = WE;
	if (env->side == 0 && env->raydir.x >= 0)
		env->tex.dir = SO;
	if (env->side == 1 && env->raydir.y >= 0)
		env->tex.dir = EA;
}

/*
** On calcule la valeur de wallx, où exactement le mur a été touché.
** On calcule tex.x, coordonnée x sur la texture.
** floor() -> calc l'arrondi entier inférieur de la valeur donnée en paramètre
** Le tex.step : de combien augmenter la coordonnée de texture par pixel d'écran
** tex.pos : coordonnée de départ de la texture
*/

void		calc_texture(t_env *env)
{
	get_texdir(env);
	if (env->side == 0)
		env->tex.wallx = env->ply.y + env->pwdist * env->raydir.y;
	else
		env->tex.wallx = env->ply.x + env->pwdist * env->raydir.x;
	env->tex.wallx -= floor((env->tex.wallx));
	env->tex.x = (int)(env->tex.wallx * (double)env->tx[env->tex.dir].width);
	if (env->side == 0 && env->raydir.x > 0)
		env->tex.x = env->tx[env->tex.dir].width - env->tex.x - 1;
	if (env->side == 1 && env->raydir.y < 0)
		env->tex.x = env->tx[env->tex.dir].width - env->tex.x - 1;
	env->tex.step = 1.0 * env->tx[0].height / env->lineh;
	env->tex.pos = (env->dstart - env->res.y / 2 + env->lineh / 2) \
					* env->tex.step;
}

static void	get_data(t_env *env)
{
	env->tx[NO].data = (int *)mlx_get_data_addr(env->tx[NO].image, \
	&env->tx[NO].bits_per_pixel, &env->tx[NO].size_line, &env->tx[NO].endian);
	env->tx[WE].data = (int *)mlx_get_data_addr(env->tx[WE].image, \
	&env->tx[WE].bits_per_pixel, &env->tx[WE].size_line, &env->tx[WE].endian);
	env->tx[SO].data = (int *)mlx_get_data_addr(env->tx[SO].image, \
	&env->tx[SO].bits_per_pixel, &env->tx[SO].size_line, &env->tx[SO].endian);
	env->tx[EA].data = (int *)mlx_get_data_addr(env->tx[EA].image, \
	&env->tx[EA].bits_per_pixel, &env->tx[EA].size_line, &env->tx[EA].endian);
	env->tx[S].data = (int *)mlx_get_data_addr(env->tx[S].image, \
	&env->tx[S].bits_per_pixel, &env->tx[S].size_line, &env->tx[S].endian);
}

void		get_texture(t_env *env)
{
	if (!(env->tx[NO].image = mlx_xpm_file_to_image(env->mlx, \
		env->tex.path_no, &env->tx[NO].width, &env->tx[NO].height)))
		print_error(env, WRONG_NO);
	if (!(env->tx[WE].image = mlx_xpm_file_to_image(env->mlx, \
		env->tex.path_we, &env->tx[WE].width, &env->tx[WE].height)))
		print_error(env, WRONG_WE);
	if (!(env->tx[SO].image = mlx_xpm_file_to_image(env->mlx, \
		env->tex.path_so, &env->tx[SO].width, &env->tx[SO].height)))
		print_error(env, WRONG_SO);
	if (!(env->tx[EA].image = mlx_xpm_file_to_image(env->mlx, \
		env->tex.path_ea, &env->tx[EA].width, &env->tx[EA].height)))
		print_error(env, WRONG_EA);
	if (!(env->tx[S].image = mlx_xpm_file_to_image(env->mlx, \
		env->tex.path_s, &env->tx[S].width, &env->tx[S].height)))
		print_error(env, WRONG_S);
	get_data(env);
}

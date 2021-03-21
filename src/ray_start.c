/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:05:43 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 19:49:16 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** calculer le pas et le sideDist initial
*/

static void	calc_sidedist(t_env *env)
{
	if (env->raydir.x < 0)
	{
		env->step.x = -1;
		env->sidedist.x = (env->ply.x - env->map.x) * env->deltadist.x;
	}
	else
	{
		env->step.x = 1;
		env->sidedist.x = (env->map.x + 1.0 - env->ply.x) * env->deltadist.x;
	}
	if (env->raydir.y < 0)
	{
		env->step.y = -1;
		env->sidedist.y = (env->ply.y - env->map.y) * env->deltadist.y;
	}
	else
	{
		env->step.y = 1;
		env->sidedist.y = (env->map.y + 1.0 - env->ply.y) * env->deltadist.y;
	}
}

/*
** On exécute DDA
** On passe au carré suivant de la carte, dans la direction x,
** OU dans la direction y
**
** env->side = 0; -> c'est un cote x qui est touche (vertical)
** env->side = 1; -> c'est un cote y qui est touche (horizontal)
** Enfin on vérifie si le rayon a heurté un mur
*/

static void	algo_dda(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->sidedist.x < env->sidedist.y)
		{
			env->sidedist.x += env->deltadist.x;
			env->map.x += env->step.x;
			env->side = 0;
		}
		else
		{
			env->sidedist.y += env->deltadist.y;
			env->map.y += env->step.y;
			env->side = 1;
		}
		if (env->map.map[env->map.x][env->map.y] == '1')
			env->hit = 1;
	}
}

/*
** On calcule (pwdist) la distance projetée sur la direction de la caméra
** (la distance euclidienne donnera un effet fisheye!).
** On calcule (lineh) la hauteur de la colonne à dessiner sur l'écran.
** On calcule (dstart / dend) le pixel le plus bas et le plus élevé
** pour remplir la bande courante.
*/

static void	calc_column(t_env *env)
{
	if (env->side == 0)
		env->pwdist = (env->map.x - env->ply.x +
						(1 - env->step.x) / 2) / env->raydir.x;
	else
		env->pwdist = (env->map.y - env->ply.y +
						(1 - env->step.y) / 2) / env->raydir.y;
	env->lineh = (int)(env->res.y / env->pwdist);
	env->dstart = -env->lineh / 2 + env->res.y / 2;
	if (env->dstart < 0)
		env->dstart = 0;
	env->dend = env->lineh / 2 + env->res.y / 2;
	if (env->dend >= env->res.y || env->dend < 0)
		env->dend = env->res.y - 1;
	env->zbuffer[env->x] = env->pwdist;
}

/*
** mspeed -> la valeur constante est en carrés / seconde
** rspeed -> la valeur constante est en radians / seconde
*/

static int	game_update(t_env *env)
{
	keys_control(env);
	env->x = -1;
	while (++env->x < env->res.x)
	{
		init_env(env);
		calc_sidedist(env);
		algo_dda(env);
		calc_column(env);
		calc_texture(env);
		draw_column(env);
	}
	if (env->nbsprite > 0)
		sprite_casting(env);
	if (env->save == 1)
		save_bmp(env);
	else
	{
		mlx_put_image_to_window(env->mlx, env->window, env->img.image, 0, 0);
		mlx_destroy_image(env->mlx, env->img.image);
		if (!(env->img.image = mlx_new_image(env->mlx, env->res.x, env->res.y)))
			print_error(env, NEW_IMAGE);
		env->img.data = (int*)mlx_get_data_addr(env->img.image, \
			&env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	}
	return (0);
}

int			start_mlx(t_env *env)
{
	init_start_mlx(env);
	if ((env->mlx = mlx_init()) == NULL)
		print_error(env, MLX_INIT);
	screen_size(env);
	get_texture(env);
	if (!(env->window = mlx_new_window(env->mlx, env->res.x, env->res.y, "<3")))
		print_error(env, NEW_WINDOW);
	if (!(env->img.image = mlx_new_image(env->mlx, env->res.x, env->res.y)))
		print_error(env, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image,
			&env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	ft_putstr_fd("Le temps est bon, le ciel est bleu !\n", 1);
	if (env->save == 1)
		game_update(env);
	else
	{
		mlx_hook(env->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, env);
		mlx_hook(env->window, KEYPRESS, KEYPRESSMASK, ft_key_press, env);
		mlx_hook(env->window, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
		mlx_loop_hook(env->mlx, game_update, env);
		mlx_loop(env->mlx);
	}
	return (0);
}

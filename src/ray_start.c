/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:05:43 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 09:21:53 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sidedist(t_env *env)
{
	// calculer le pas et le sideDist initial
	if (env->raydir.x < 0)
	{
		env->step.x = -1;
		env->sidedist.x = (env->player.px - env->map.x) * env->deltadist.x;
	}
	else
	{
		env->step.x = 1;
		env->sidedist.x = (env->map.x + 1.0 - env->player.px) * env->deltadist.x;
	}
	if (env->raydir.y < 0)
	{
		env->step.y = -1;
		env->sidedist.y = (env->player.py - env->map.y) * env->deltadist.y;
	}
	else
	{
		env->step.y = 1;
		env->sidedist.y = (env->map.y + 1.0 - env->player.py) * env->deltadist.y;
	}
}

void	algo_dda(t_env *env)
{
	// exécute DDA
	while (env->hit == 0)
	{
		// passe au carré suivant de la carte, OU dans la direction x, OU dans la direction y
		if (env->sidedist.x < env->sidedist.y)
		{
			env->sidedist.x += env->deltadist.x;
			env->map.x += env->step.x;
			env->side = 0; // c'est un cote x qui est touche (vertical)
		}
		else
		{
			env->sidedist.y += env->deltadist.y;
			env->map.y += env->step.y;
			env->side = 1; // c'est un cote y qui est touche (horizontal)
		}
		// Vérifie si le rayon a heurté un mur
		if(env->map.map[env->map.x][env->map.y] == '1')
			env->hit = 1;
	}
}

void	calc_column(t_env *env)
{
	// Calculer la distance projetée sur la direction de la caméra (la distance euclidienne donnera un effet fisheye!)
	if (env->side == 0)
		env->pwdist = (env->map.x - env->player.px + (1 - env->step.x) / 2) / env->raydir.x;
	else
		env->pwdist = (env->map.y - env->player.py + (1 - env->step.y) / 2) / env->raydir.y;

	// Calcule la hauteur de la colonne à dessiner sur l'écran
	env->lineh = (int)(env->res.y / env->pwdist); // env->res.y -> h = hauteur fenetre !

	// calcule le pixel le plus bas et le plus élevé pour remplir la bande courante
	env->dstart = -env->lineh / 2 + env->res.y / 2;
	if (env->dstart < 0)
		env->dstart = 0;
	env->dend = env->lineh / 2 + env->res.y / 2;
	if (env->dend >= env->res.y || env->dend < 0)
		env->dend = env->res.y - 1;
}

int	game_update(t_env *env)
{
	env->player.mspeed = 0.1; // la valeur constante est en carrés / seconde
	env->player.rspeed =  0.033 * 1.8; // la valeur constante est en radians / seconde
	keys_control(env);
	// ft_bzero(env->img.data, env->img.size_line * env->res.y);
	env->x = 0;
	while (env->x < env->res.x)
	{
		init_env(env);
		calc_sidedist(env);
		algo_dda(env);
		calc_column(env);
		calc_texture(env);
		draw_column(env, env->x);
		env->x++;
	}
	mlx_put_image_to_window(env->mlx, env->window, env->img.image, 0, 0);
	mlx_destroy_image(env->mlx, env->img.image);
	if (!(env->img.image = mlx_new_image(env->mlx, env->res.x, env->res.y)))
		print_error(env, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	return (0);
}

int	start_mlx(t_env *env)
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
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	ft_putstr_fd("Le temps est bon, le ciel est bleu !\n", 1);
	mlx_hook(env->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, env);
	mlx_hook(env->window, KEYPRESS, KEYPRESSMASK, ft_key_press, env);
	mlx_hook(env->window, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
	mlx_loop_hook(env->mlx, game_update, env);
	mlx_loop(env->mlx);
	return (0);
}
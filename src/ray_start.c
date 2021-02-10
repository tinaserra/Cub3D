/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:05:43 by vserra            #+#    #+#             */
/*   Updated: 2021/02/10 13:19:21 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sidedist(t_env *env)
{
	// calculer le pas et le sideDist initial
	if (env->rayDirX < 0)
	{
		env->stepX = -1;
		env->sideDistX = (env->parse.player.px - env->mapX) * env->deltaDistX;
		// printf("env->sideDistX = %f\n", env->sideDistX);
	}
	else
	{
		env->stepX = 1;
		env->sideDistX = (env->mapX + 1.0 - env->parse.player.px) * env->deltaDistX;
		// printf("env->sideDistX = %f\n", env->sideDistX);
	}
	if (env->rayDirY < 0)
	{
		env->stepY = -1;
		env->sideDistY = (env->parse.player.py - env->mapY) * env->deltaDistY;
		// printf("env->sideDistY = %f\n", env->sideDistY);
	}
	else
	{
		env->stepY = 1;
		env->sideDistY = (env->mapY + 1.0 - env->parse.player.py) * env->deltaDistY;
		// printf("env->sideDistY = %f\n", env->sideDistY);
	}
}

void	algo_dda(t_env *env)
{
	// exécute DDA
	while (env->hit == 0)
	{
		// passe au carré suivant de la carte, OU dans la direction x, OU dans la direction y
		if (env->sideDistX < env->sideDistY)
		{
			env->sideDistX += env->deltaDistX;
			env->mapX += env->stepX;
			env->side = 0; // c'est un cote x qui est touche (vertical)
		}
		else
		{
			env->sideDistY += env->deltaDistY;
			env->mapY += env->stepY;
			env->side = 1; // c'est un cote y qui est touche (horizontal)
		}
		// Vérifie si le rayon a heurté un mur
		if(env->parse.map[env->mapX][env->mapY] == '1')
			env->hit = 1;
	}
}

void	calc_column(t_env *env)
{
	// Calculer la distance projetée sur la direction de la caméra (la distance euclidienne donnera un effet fisheye!)
	if (env->side == 0)
		env->perpWallDist = (env->mapX - env->parse.player.px + (1 - env->stepX) / 2) / env->rayDirX;
	else
		env->perpWallDist = (env->mapY - env->parse.player.py + (1 - env->stepY) / 2) / env->rayDirY;

	// Calcule la hauteur de la colonne à dessiner sur l'écran
	env->lineHeight = (int)(env->parse.resy / env->perpWallDist); // env->parse.resy -> h = hauteur fenetre !

	// calcule le pixel le plus bas et le plus élevé pour remplir la bande courante
	env->drawStart = -env->lineHeight / 2 + env->parse.resy / 2;
	if (env->drawStart < 0)
		env->drawStart = 0;
	env->drawEnd = env->lineHeight / 2 + env->parse.resy / 2;
	if (env->drawEnd >= env->parse.resy || env->drawEnd < 0)
		env->drawEnd = env->parse.resy - 1;
}

int	game_update(t_env *env)
{
	env->moveSpeed = 0.1; // la valeur constante est en carrés / seconde
	env->rotSpeed =  0.033 * 1.8; // la valeur constante est en radians / seconde
	void	keys_control(t_env *env);
	// ft_bzero(env->img.data, env->img.size_line * env->parse.resy);
	env->x = 0;
	while (env->x < env->parse.resx)
	{
		init_env(env);
		calc_sidedist(env);
		algo_dda(env);
		calc_column(env);
		draw_column(env, env->x);
		env->x++;
	}
	mlx_put_image_to_window(env->mlx, env->window, env->img.image, 0, 0);
	mlx_destroy_image(env->mlx, env->img.image);
	if (!(env->img.image = mlx_new_image(env->mlx, env->parse.resx, env->parse.resy)))
		print_error(&env->parse, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	return (0);
}

int	start_mlx(t_env *env)
{
	init_start_mlx(env);
	if ((env->mlx = mlx_init()) == NULL)
		print_error(&env->parse, MLX_INIT);
	// screen_size(env);
	if (!(env->window = mlx_new_window(env->mlx, env->parse.resx, env->parse.resy, "Mon super titre")))
		print_error(&env->parse, NEW_WINDOW);
	if (!(env->img.image = mlx_new_image(env->mlx, env->parse.resx, env->parse.resy)))
		print_error(&env->parse, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	ft_putstr_fd("Le temps est bon, le ciel est bleu !\n", 1);
	mlx_hook(env->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, env);
	mlx_hook(env->window, KEYPRESS, KEYPRESSMASK, ft_key_press, env);
	mlx_hook(env->window, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
	mlx_loop_hook(env->mlx, game_update, env);
	mlx_loop(env->mlx);
	return (0);
}
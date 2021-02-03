/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:05:43 by vserra            #+#    #+#             */
/*   Updated: 2021/02/03 10:39:38 by vserra           ###   ########.fr       */
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

void	calc_player_to_wall(t_env *env)
{
	// Calculer la distance projetée sur la direction de la caméra (la distance euclidienne donnera un effet fisheye!)
	if (env->side == 0)
		env->perpWallDist = (env->mapX - env->parse.player.px + (1 - env->stepX) / 2) / env->rayDirX;
	else
		env->perpWallDist = (env->mapY - env->parse.player.py + (1 - env->stepY) / 2) / env->rayDirY;
}

void	calc_column(t_env *env)
{
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

int		ret_color(t_env *env, int alpha, int red, int green, int blue)
{
	int all;

	t_color color;
	color.argb[BGRA_ALPHA] = alpha;
	color.argb[BGRA_RED] = red;
	color.argb[BGRA_GREEN] = green;
	color.argb[BGRA_BLUE] = blue;
	all = ft_convert_color(color, env->img.endian);
	return (all);
}

void	draw_column(t_env *env, int coord_x)
{
	// dessine les pixels de la bande comme une ligne verticale
	int color; // couleur
	int y = 0;
	// dessine le plafond
	while (y < env->drawStart)
	{
		color = ret_color(env, 0, env->parse.col.red_c, env->parse.col.green_c, env->parse.col.blue_c);
		put_px_to_img(&env->img, coord_x, y, color);
		y++;
	}
	// dessine le mur
	while (y <= env->drawEnd)
	{
		color = ret_color(env, 0, 255, 167, 95);
		// donne aux côtés x et y une luminosité différente
		if (env->side == 1)
			color = color / 2;
		put_px_to_img(&env->img, coord_x, y, color);
		y++;
	}
	// dessine le sol
	while (y < env->parse.resy)
	{
		color = ret_color(env, 0, env->parse.col.red_f, env->parse.col.green_f, env->parse.col.blue_f);
		put_px_to_img(&env->img, coord_x, y, color);
		y++;
	}
}

int	game_update(t_env *env)
{
	env->x = 0;
	ft_bzero(env->img.data, env->img.size_line * env->parse.resy);
	while (env->x < env->parse.resx)
	{
		init_env(env);
		calc_sidedist(env);
		algo_dda(env);
		calc_player_to_wall(env);
		calc_column(env);
		draw_column(env, env->x);
		env->x++;
	}

	// timing pour l'entrée et le compteur FPS
	// env->oldTime = env->time;
	// env->time = getTicks();
	// env->frameTime = (env->time - env->oldTime) / 1000.0; // frameTime est le temps que cette image a pris, en secondes
	// print(1.0 / env->frameTime); // Compteur FPS
	// redraw();
	// cls();

	// // modificateurs de vitesse
	// env->moveSpeed = env->frameTime * 5.0; // la valeur constante est en carrés / seconde
	// env->rotSpeed = env->frameTime * 3.0; // la valeur constante est en radians / seconde


	if (env->keyboard[KEY_ESCAPE])
		ft_quit(env);

	// avance si pas de mur devant toi
	if (env->keyboard[KEY_W]) // (keyDown(SDLK_UP))
	{
		if (env->parse.map[(int)(env->parse.player.px + env->parse.player.dirX /** env->moveSpeed*/)][(int)(env->parse.player.py)] == '0')
			env->parse.player.px += env->parse.player.dirX /** env->moveSpeed*/;
		if (env->parse.map[(int)(env->parse.player.px)][(int)(env->parse.player.py + env->parse.player.dirY /** env->moveSpeed)*/)] == '0')
			env->parse.player.py += env->parse.player.dirY /** env->moveSpeed*/;
	}
	// recule si aucun mur derrière vous
	if (env->keyboard[KEY_S]) // (keyDown(SDLK_DOWN))
	{
		if (env->parse.map[(int)(env->parse.player.px - env->parse.player.dirX /** env->moveSpeed*/)][(int)(env->parse.player.py)] == '0')
			env->parse.player.px -= env->parse.player.dirX /** env->moveSpeed*/;
		if (env->parse.map[(int)(env->parse.player.px)][(int)(env->parse.player.py - env->parse.player.dirY /** env->moveSpeed*/)] == '0')
			env->parse.player.py -= env->parse.player.dirY /** env->moveSpeed*/;
	}
	// tourner vers la droite
	if (env->keyboard[KEY_D]) // (keyDown(SDLK_RIGHT))
	{
		// La direction de la caméra et le plan de la caméra doivent être tournés
		double oldDirX = env->parse.player.dirX;
		env->parse.player.dirX = env->parse.player.dirX * cos(-env->rotSpeed) - env->parse.player.dirY * sin(-env->rotSpeed);
		env->parse.player.dirY = oldDirX * sin(-env->rotSpeed) + env->parse.player.dirY * cos(-env->rotSpeed);
		double oldPlaneX = env->planeX;
		env->planeX = env->planeX * cos(-env->rotSpeed) - env->planeY * sin(-env->rotSpeed);
		env->planeY = oldPlaneX * sin(-env->rotSpeed) + env->planeY * cos(-env->rotSpeed);
	}
	// tourner vers la gauche
	if (env->keyboard[KEY_A]) // (keyDown(SDLK_LEFT))
	{
		// La direction de la caméra et le plan de la caméra doivent être tournés
		double oldDirX = env->parse.player.dirX;
		env->parse.player.dirX = env->parse.player.dirX * cos(env->rotSpeed) - env->parse.player.dirY * sin(env->rotSpeed);
		env->parse.player.dirY = oldDirX * sin(env->rotSpeed) + env->parse.player.dirY * cos(env->rotSpeed);
		double oldPlaneX = env->planeX;
		env->planeX = env->planeX * cos(env->rotSpeed) - env->planeY * sin(env->rotSpeed);
		env->planeY = oldPlaneX * sin(env->rotSpeed) + env->planeY * cos(env->rotSpeed);
	}

	mlx_put_image_to_window(env->mlx, env->window, env->img.image, 0, 0);
	return (0);
}

int	start_mlx(t_env *env)
{
	// env->parse.player.px = env->parse.player.px; // position de départ du joueur x
	// env->parse.player.py = env->parse.player.py; // position de départ du joueur y
	env->planeX = 0;
	env->planeY = 0.66; // la version 2D raycaster du plan de la caméra

	env->time = 0; // heure de la trame courante
	env->oldTime = 0; // heure de l'image précédente

	if ((env->mlx = mlx_init()) == NULL)
		mlx_error(&env->parse, MLX_INIT);
	// screen_size(env);
	if (!(env->window = mlx_new_window(env->mlx, env->parse.resx, env->parse.resy, "Mon super titre")))
		mlx_error(&env->parse, NEW_WINDOW);
	if (!(env->img.image = mlx_new_image(env->mlx, env->parse.resx, env->parse.resy)))
		mlx_error(&env->parse, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	ft_putstr_fd("Le temps est bon, le ciel est bleu !\n", 1);
	mlx_hook(env->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, env);
	mlx_hook(env->window, KEYPRESS, KEYPRESSMASK, ft_key_press, env);
	mlx_hook(env->window, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
	mlx_loop_hook(env->mlx, game_update, env);
	mlx_loop(env->mlx);
	return (0);
}
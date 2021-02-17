/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:05:43 by vserra            #+#    #+#             */
/*   Updated: 2021/02/17 19:44:30 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sidedist(t_env *env)
{
	// calculer le pas et le sideDist initial
	if (env->raydirx < 0)
	{
		env->stepx = -1;
		env->sidedistx = (env->player.px - env->map.x) * env->deltadistx;
	}
	else
	{
		env->stepx = 1;
		env->sidedistx = (env->map.x + 1.0 - env->player.px) * env->deltadistx;
	}
	if (env->raydiry < 0)
	{
		env->stepy = -1;
		env->sidedisty = (env->player.py - env->map.y) * env->deltadisty;
	}
	else
	{
		env->stepy = 1;
		env->sidedisty = (env->map.y + 1.0 - env->player.py) * env->deltadisty;
	}
}

void	algo_dda(t_env *env)
{
	// exécute DDA
	while (env->hit == 0)
	{
		// passe au carré suivant de la carte, OU dans la direction x, OU dans la direction y
		if (env->sidedistx < env->sidedisty)
		{
			env->sidedistx += env->deltadistx;
			env->map.x += env->stepx;
			env->side = 0; // c'est un cote x qui est touche (vertical)
		}
		else
		{
			env->sidedisty += env->deltadisty;
			env->map.y += env->stepy;
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
		env->pwalldist = (env->map.x - env->player.px + (1 - env->stepx) / 2) / env->raydirx;
	else
		env->pwalldist = (env->map.y - env->player.py + (1 - env->stepy) / 2) / env->raydiry;

	// Calcule la hauteur de la colonne à dessiner sur l'écran
	env->lineheight = (int)(env->res.y / env->pwalldist); // env->res.y -> h = hauteur fenetre !

	// calcule le pixel le plus bas et le plus élevé pour remplir la bande courante
	env->drawstart = -env->lineheight / 2 + env->res.y / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = env->lineheight / 2 + env->res.y / 2;
	if (env->drawend >= env->res.y || env->drawend < 0)
		env->drawend = env->res.y - 1;
}

int	game_update(t_env *env)
{
	env->movespeed = 0.1; // la valeur constante est en carrés / seconde
	env->rotspeed =  0.033 * 1.8; // la valeur constante est en radians / seconde
	void	keys_control(t_env *env);
	// ft_bzero(env->img.data, env->img.size_line * env->res.y);
	env->x = 0;
	while (env->x < env->res.x)
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
	if (!(env->img.image = mlx_new_image(env->mlx, env->res.x, env->res.y)))
		print_error(env, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	return (0);
}

// recup->texture[0].addr = (int *)mlx_get_data_addr(recup->texture[0].img, &recup->texture[0].bits_per_pixel, &recup->texture[0].line_length, &recup->texture[0].endian);

// if (!(recup->texture[0].img = mlx_xpm_file_to_image(recup->data.mlx_ptr, recup->no, &(recup->texture[0].width), &(recup->texture[0].height))))
// 		ft_error(recup, "Texture SO\n");

// void	get_texture(t_env *env)
// {
// 	env->img.image = mlx_xpm_file_to_image(env->mlx, env->parse.path_no, env->)
// }

int	start_mlx(t_env *env)
{
	init_start_mlx(env);
	if ((env->mlx = mlx_init()) == NULL)
		print_error(env, MLX_INIT);
	// screen_size(env);
	// get_texture(env);
	if (!(env->window = mlx_new_window(env->mlx, env->res.x, env->res.y, "Mon super titre")))
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
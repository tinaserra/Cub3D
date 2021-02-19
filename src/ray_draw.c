/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:24:16 by vserra            #+#    #+#             */
/*   Updated: 2021/02/19 16:40:48 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_px_to_img(t_image *img, int x, int y, int color)
{
	img->data[y * (img->size_line / 4) + x] = color;
}

/*
** *(int *)&img->data[img->size_line * y + x * img->bits_per_pixel / 8] = color;
**
** size_line == taille de ligne de l image.
** bits_per_pixel == un nombre de bit pour un pixel en memoire.
**
** pour avancer de ligne en ligne avec un buffer de une dimmension : avancer de size_ligne en size_ligne.
** Pour avancer d un pixel dans une ligne il faut avancer de bite par pixel / 8. (un byte = 8 bites)
** Mettre un int dans un char* = on recupere l adresse de data(&). on le cast en int*. + *devant pour y acceder.
**
** on cast directement la fontion mlx_get_data_adr du coup on le stock dans un int *data.
** on peux supprimer le cast du debut, puisque c est deja un int qu on veux mettre dans un int.
** vu que c est int int* on avance de 4. donc on supprime le '* img->bits_per_pixel / 8' car c etait = 4.
*/

void	put_tex_to_img(t_env *env, int x, int y)
{
	(void)y;
	(void)x;
	(void)env;
	env->img.data[y * env->img.size_line / 4 + x] = env->tx[env->tex.dir].data[env->tex.y * env->tx[env->tex.dir].size_line / 4 + env->tex.x];
	printf("NIQUE TA MAMIE\n");
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

void	draw_texture(t_env *env, int x, int y)
{
	// y = env->wall.dstart - 1;
	// while (++y <= env->wall.dend)
	// {
		// Convertit la coordonnée de la texture en entier, et masque avec (texHeight - 1) en cas de débordement
		env->tex.y = (int)env->tex.pos & (env->tx[env->tex.dir].height - 1);
		env->tex.pos += env->tex.step;
		if (y < env->res.y && x < env->res.x)
		{
			// printf("NIQUE TA MAMAN\n");
			put_px_to_img(&env->img, x, y, env->tx[env->tex.dir].data[env->tex.y * env->tx[env->tex.dir].size_line / 4 + env->tex.x]);
			// env->img.data[y * (env->img.size_line / 4) + x] = 3289650;//env->tx[env->tex.dir].data[env->tex.y * env->tx[env->tex.dir].size_line / 4 + env->tex.x];
		}
			
	// }
}

void	ta_maman_la_tchoin(t_env *env)
{
		init_texture(env);
	// calculer la valeur de wallx, où exactement le mur a été touché
	if (env->wall.side == 0)
		env->tex.wallx = env->player.py + env->wall.pdist * env->raydir.y;
	else
		env->tex.wallx = env->player.px + env->wall.pdist * env->raydir.x;
	env->tex.wallx -= floor((env->tex.wallx)); // calcule l'arrondi entier inférieur de la valeur spécifiée en paramètre
	// coordonnée x sur la texture
	env->tex.x = (int)(env->tex.wallx * (double)env->tx[env->tex.dir].width);
	if (env->wall.side == 0 && env->raydir.x > 0)
		env->tex.x = env->tx[env->tex.dir].width - env->tex.x - 1;
	if (env->wall.side == 1 && env->raydir.y < 0)
		env->tex.x = env->tx[env->tex.dir].width - env->tex.x - 1;
	// De combien augmenter la coordonnée de texture par pixel d'écran
	env->tex.step = 1.0 * env->tx[0].height / env->wall.lineh;
	// Coordonnée de départ de la texture
	env->tex.pos = (env->wall.dstart - env->res.y / 2 + env->wall.lineh / 2) * env->tex.step;
}

void	draw_column(t_env *env, int coord_x)
{
	int y;
	int color;
	y = -1;
	while (++y < env->res.y)
	{
		// dessine le mur
		// printf("env->wall.dstart = %d\n", env->wall.dstart);
		// printf("y = %d\n", y);
		if (y >= env->wall.dstart && y <= env->wall.dend)
		{
			// color = ret_color(env, 0, 255, 167, 95);
			// put_px_to_img(&env->img, coord_x, y, color);
			draw_texture(env, env->x, y);
		}
		// dessine le plafond
		else if (y < env->res.y / 2)
		{
			color = ret_color(env, 0, env->col.red_c, env->col.green_c, env->col.blue_c);
			put_px_to_img(&env->img, coord_x, y, color);
		}
		// dessine le sol
		else
		{
			color = ret_color(env, 0, env->col.red_f, env->col.green_f, env->col.blue_f);
			put_px_to_img(&env->img, coord_x, y, color);
		}
	}
}

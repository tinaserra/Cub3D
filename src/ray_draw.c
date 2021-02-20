/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:24:16 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 11:13:54 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_px_to_img(t_image *img, int x, int y, int color)
{
	img->data[y * (img->size_line / 4) + x] = color;
}

/*
** *(int *)&img->data[img->size_line * y + x * img->bits_per_pixel / 8] = color;
**
** size_line == taille de ligne de l image.
** bits_per_pixel == un nombre de bit pour un pixel en memoire.
**
** Pour avancer de ligne en ligne avec un buffer de une dimmension : avancer de size_ligne en size_ligne.
** Pour avancer d un pixel dans une ligne il faut avancer de bite par pixel / 8. (un byte = 8 bites)
** Mettre un int dans un char* = on recupere l adresse de data(&). on le cast en int*. + *devant pour y acceder.
**
** on cast directement la fontion mlx_get_data_adr du coup on le stock dans un int *data.
** on peux supprimer le cast du debut, puisque c est deja un int qu on veux mettre dans un int.
** vu que c est int int* on avance de 4. donc on supprime le '* img->bits_per_pixel / 8' car c etait = 4.
*/

static int	ret_color(t_env *env, int alpha, int red, int green, int blue)
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

/*
** Convertit la coordonnée de la texture en entier,
** et masque avec (texHeight - 1) en cas de débordement.
*/

static void	draw_texture(t_env *env, int x, int y)
{
	env->tex.y = (int)env->tex.pos & (env->tx[env->tex.dir].height - 1);
	env->tex.pos += env->tex.step;
	if (y < env->res.y && x < env->res.x)
		put_px_to_img(&env->img, x, y, \
		env->tx[env->tex.dir].data[env->tex.y * \
		env->tx[env->tex.dir].size_line / 4 + env->tex.x]);
}

/*
** [1] On dessine le mur
** [2] On dessine le plafond
** [3] On dessine le sol
*/

void	draw_column(t_env *env, int coord_x)
{
	int y;
	int color;
	y = -1;
	while (++y < env->res.y)
	{
		if (y >= env->dstart && y <= env->dend)
			draw_texture(env, env->x, y);
		else if (y < env->res.y / 2)
		{
			color = ret_color(env, 0, env->col.red_c, env->col.green_c, env->col.blue_c);
			put_px_to_img(&env->img, coord_x, y, color);
		}
		else
		{
			color = ret_color(env, 0, env->col.red_f, env->col.green_f, env->col.blue_f);
			put_px_to_img(&env->img, coord_x, y, color);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:24:16 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 17:22:43 by vserra           ###   ########.fr       */
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
** [1] On dessine le mur
** [2] On dessine le plafond
** [3] On dessine le sol
*/

void	draw_column(t_env *env)
{
	int y;
	int color;
	y = -1;
	while (++y < env->res.y)
	{
		if (y >= env->dstart && y <= env->dend)
		{
			// draw_texture(env, env->x, y);
			put_px_to_img(&env->img,env->x, y, \
			env->tx[env->tex.dir].data[(int)env->tex.pos * \
			env->tx[env->tex.dir].size_line / 4 + env->tex.x]);
			env->tex.pos += env->tex.step;
		}
		else if (y <= env->res.y / 2)
		{
			color = ret_color(env, 0, env->c.red, env->c.green, env->c.blue);
			put_px_to_img(&env->img, env->x, y, color);
		}
		else
		{
			color = ret_color(env, 0, env->f.red, env->f.green, env->f.blue);
			put_px_to_img(&env->img, env->x, y, color);
		}
	}
}

/*
** Pour chaque colonne (x) du sprite à l'écran
**
** Les conditions dans le if sont:
** 1) c'est devant le plan de la caméra donc vous ne voyez pas les choses derrière vous
** 2) c'est sur l'écran (à gauche)
** 3) c'est sur l'écran (à droite)
** 4) ZBuffer, avec une distance perpendiculaire
**
** 256 et 128 facteurs pour éviter les flottants.
** Récupérer la couleur actuelle de la texture.
** Peindre le pixel s'il n'est pas noir, le noir est la couleur invisible.
*/


void	draw_sprite(t_env *env, int i)
{
	int y;
	int x = env->spr[i].dstart.x;

	// boucle à travers chaque bande verticale du sprite à l'écran
	while (x < env->spr[i].dend.x)
	{
		env->spr[i].tex.x = (int)(256 * (x - (-env->spr[i].w / 2 + \
					env->spr[i].sx)) * env->tx[S].width / env->spr[i].w) / 256;
		if (env->spr[i].tform.y > 0 && x > 0 && x < env->res.x \
			&& env->spr[i].tform.y < env->zbuffer[x])
		{
			// pour chaque pixel de la bande courante
			y = env->spr[i].dstart.y;
			while (y < env->spr[i].dend.y)
			{
				env->spr[i].tex.y = (((y * 256 - env->res.y * 128 + env->spr[i].h
				* 128) * env->tx[S].height) / env->spr[i].h) / 256;
				env->spr[i].color = env->tx[S].data[env->spr[i].tex.y \
									* 64 + env->spr[i].tex.x];
				if (env->spr[i].color != 0)
					put_px_to_img(&env->img, x, y, env->spr[i].color);
				y++;
			}
		}
		x++;
	}
}

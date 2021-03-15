/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:16:21 by vserra            #+#    #+#             */
/*   Updated: 2021/03/15 17:11:44 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprite_coord(t_env *env)
{
	int y;
	int x;
	int i;

	if (!(env->spr = malloc(sizeof(t_sprite) * env->nbsprite)))
		print_error(env, MALLOC_FAILED);
	y = 0;
	i = 0;
	while (y < env->nbsprite)
	{
		x = 0;
		while (env->map.map[y][x])
		{
			if (env->map.map[y][x] == '2')
			{
				env->spr[i].x = x;
				env->spr[i].y = y;
				i++;
			}
			x++;
		}
		y++;
	}
}

/*
** Calculer les distances entre le joueur et chaque sprite
*/

void	dist_sprite_player(t_env *env)
{
	int i;
	
	i = 0;
	while (i < env->nbsprite - 1)
	{
		env->spr[i].dist = sqrt(pow(env->ply.x - env->spr[i].x, 2)
			+ pow(env->ply.y - env->spr[i].y, 2));
		// env->spr[i].dist = sqrt(pow(env->ply.x - env->spr[i].x)
		// 	* (env->ply.x - env->spr[i].x) + (env->ply.y - env->spr[i].y)
		// 	* (env->ply.y - env->spr[i].y)) ;
		i++;
	}
}

/*
** Trier les sprites de loin à pret
*/

// void	sort_sprite(t_env *env)
// {
// 	int i;
// 	int a;  

// 	dist_sprite_player(env);
// 	i = 0;
// 	while (i < env->nbsprite)
// 	{
// 		if (env->spr[i].dist > env->spr[i + 1].dist)
// 		{
// 			ft_swap(&env->spr[i].dist, & env->spr[i + 1].dist);
// 			a = i;
// 		}
// 		while (a)
// 		{
// 			if (env->spr[i - 1].dist > env->spr[a].dist)
// 			{
// 				ft_swap(&env->spr[a - 1].dist, &env->spr[a].dist);
// 				--a;
// 			}
// 			else
// 				a = 0;
// 		}
// 		i++;
// 	}
// }


void	sort_sprite(t_env *env)
{
	int i;
	t_sprite tmp;

	i = 0;
	dist_sprite_player(env);
	while (i < env->nbsprite - 1)
	{
		if (env->spr[i].dist > env->spr[i + 1].dist)
		{
			// ft_swap(&env->spr[i], & env->spr[i + 1]);
			tmp = env->spr[i];
			env->spr[i] = env->spr[i + 1];
			env->spr[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

/*
** SPRITE POSITION
**
** 1. Traduit la position du sprite en relative à la caméra
** 2. Calculer invdet : requis pour une multiplication correcte de la matrice.
** 3. tform.y : c'est en fait la profondeur à l'intérieur de l'écran, ce que Z est en 3D.
*/

void	sprite_position(t_env *env, int i)
{
	double spr_x;
	double spr_y;

	spr_x = env->spr[i].x - env->ply.x + 0.5;
	spr_y = env->spr[i].y - env->ply.y + 0.5;
	env->spr[i].invdet = 1.0 / (env->plane.x * env->ply.diry \
							- env->ply.dirx * env->plane.y);
	env->spr[i].tform.x = env->spr[i].invdet * \
						(env->ply.diry * spr_x - env->ply.dirx * spr_y);
	env->spr[i].tform.y = env->spr[i].invdet * \
						(-env->plane.y * spr_x + env->plane.x * spr_y);
	env->spr[i].sx = (int)((env->res.x / 2) * \
					(1 + env->spr[i].tform.x / env->spr[i].tform.y));
}

/*
** SPRITE CASTING
**
** 1. Calculer la hauteur du sprite à l'écran en utilisant 'tform.y' 
**    au lieu de la distance réelle empêche fisheye.
** 2. Calculer le pixel le plus bas et le plus élevé pour remplir la bande courante.
** 3. Calculer la largeur du sprite
*/

void	sprite_casting(t_env *env)
{
	int i;

	// if (!(env->zbuffer = malloc(sizeof(env->zbuffer) * env->res.x)))
	// 	print_error(env, MALLOC_FAILED);
	// printf("OOOOOOOOO \n");
	get_sprite_coord(env);
	sort_sprite(env);
	i = 0;
	while (i < env->nbsprite)
	{
		sprite_position(env, i);
		env->spr[i].h = abs((int)(env->res.y / (env->spr[i].tform.y)));


		env->spr[i].dstart.y = -env->spr[i].h / 2 + env->res.y / 2;

		if (env->spr[i].dstart.y < 0)
			env->spr[i].dstart.y = 0;
		env->spr[i].dend.y = env->spr[i].h / 2 + env->res.y / 2;
		if (env->spr[i].dend.y >= env->res.y)
			env->spr[i].dend.y = env->res.y - 1;
		env->spr[i].w = abs((int)(env->res.y / (env->spr[i].tform.y)));
		env->spr[i].dstart.x = -env->spr[i].w / 2 + env->spr[i].sx;
		if (env->spr[i].dstart.x < 0)
			env->spr[i].dstart.x = 0;
		env->spr[i].dend.x = env->spr[i].w / 2 + env->spr[i].sx;
		if (env->spr[i].dend.x >= env->res.x)
			env->spr[i].dend.x = env->res.x - 1;
		// printf("* dstart %d\n", env->spr[i].dstart.x);
		// printf("* dend %d\n", env->spr[i].dend.x);
		i++;
	}
	draw_sprite(env, i);
}

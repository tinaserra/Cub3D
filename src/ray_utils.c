/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:52 by vserra            #+#    #+#             */
/*   Updated: 2021/02/10 13:29:10 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_convert_color(t_color color, int endian)
{
	t_color	temp;

	if (endian == 1)
	{
		temp.all = color.all;
		color.bgra[BGRA_ALPHA] = color.argb[ARGB_ALPHA];
		color.bgra[BGRA_RED] = color.argb[ARGB_RED];
		color.bgra[BGRA_GREEN] = temp.argb[ARGB_GREEN];
		color.bgra[BGRA_BLUE] = temp.argb[ARGB_BLUE];
	}
	return (color.all);
}

int	ft_key_press(int key, t_env *env)
{
	env->keyboard[key] = 1;
	return (0);
}

int	ft_key_release(int key, t_env *env)
{
	env->keyboard[key] = 0;
	return (0);
}

// Fonction a changer de fichier ! 😎

void	screen_size(t_env *env)
{
	// avec mlx_get_screen_size -> connaitre la resolutiion de l'ecran utilisé,
	// si la res demandé dans le file.cub est supperieur a l'ecran alors choisr une resolution plus petite (celle de l'ecran)

	mlx_get_screen_size(env->mlx, &env->screen_width, &env->screen_height);
	if (env->parse.resx > env->screen_width)
		env->parse.resx = env->screen_width;
	if (env->parse.resy > env->screen_height)
		env->parse.resy = env->screen_height;

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:52 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 10:17:53 by vserra           ###   ########.fr       */
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

/*
** avec mlx_get_screen_size -> connaitre la resolutiion de l'ecran utilisé,
** si la resolution demandée dans le file.cub est supperieure a l'ecran
** -> on redimentionne a la taille de l'ecran.
*/

void	screen_size(t_env *env)
{
	mlx_get_screen_size(env->mlx, &env->screen_width, &env->screen_height);
	if (env->res.x > env->screen_width)
		env->res.x = env->screen_width;
	if (env->res.y > env->screen_height)
		env->res.y = env->screen_height;
}

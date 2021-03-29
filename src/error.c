/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:46:03 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 15:51:16 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

void	free_textures(t_env *env)
{
	printf("\nJE FREE LES TEXTURES FDP\n");
	if (env->tex.path_no != NULL)
		free(env->tex.path_no);
	if (env->tex.path_ea != NULL)
		free(env->tex.path_ea);
	if (env->tex.path_so != NULL)
		free(env->tex.path_so);
	if (env->tex.path_we != NULL)
		free(env->tex.path_we);
	if (env->tex.path_s != NULL)
		free(env->tex.path_s);
}

void	free_map(t_env *env)
{
	int		i;

	printf("JE FREE LA MAP LA CON DE TA MERE\n");
	i = 0;
	while (i < env->map.nb_lines - 1)
	{
		if (env->map.map[i] != NULL)
		{
			env->map.map[i] = NULL;
			free(env->map.map[i]);
		}
		i++;
	}
	free(env->map.map);
}

int			ft_quit(t_env *env)
{
	free_textures(env);
	if (env->map.map != NULL)
		free_map(env);
	printf("JE FREE LA STRUCTURE DES SPRITE ENCULÉ\n");
	if (env->spr)
		free(env->spr);
	if (env->zbuffer)
		free(env->zbuffer);
	if (env->img.image)
		mlx_destroy_image(env->mlx, env->img.image);
	if (env->window)
		mlx_destroy_window(env->mlx, env->window);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	exit(EXIT_FAILURE);
}

int		print_error(t_env *env, int error)
{
	ft_putstr_fd(g_str_error[error], 2);
	return(ft_quit(env));
}

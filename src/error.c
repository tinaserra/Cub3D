/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:46:03 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 15:39:44 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_env *env)
{
	printf("FDP\n");
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

	i = 0;
	while (i < env->map.nb_lines)
	{
		if (env->map.map[i] != NULL)
			free(env->map.map[i]);
		i++;
	}
	free(env->map.map);
}

int print_error(t_env *env, int error)
{
	free_textures(env);
	if (env->map.map != NULL)
		free_map(env);
	ft_putstr_fd(g_str_error[error], 2);
	// system("leaks Cub3D");
	exit(EXIT_FAILURE);
}

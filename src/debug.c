/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:32:40 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 14:03:39 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef DEBUG

void	debug_print_map(t_env *env)
{
	int i;
	int j;

	printf("\n\n********* DEBUG PRINT MAP *********\n\n");
	printf("nb_lines = %d\n", env->map.nb_lines);
	printf("len_line = %d\n", env->map.len_line);
	printf("Player position = %c\n", env->ply.orient_start);
	printf("Number of sprite = %d\n\n", env->nbsprite);
	printf("-------------\n|    MAP    |\n-------------\n");
	i = 0;
	while (i < env->map.nb_lines)
	{
		j = 0;
		while (env->map.map[i][j] != '\0')
		{
			if (env->map.map[i][j] == ' ')
				printf(" .");
			else
				printf("%2c", env->map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

#else

void	debug_print_map(t_env *env)
{
	(void)env;
	return ;
}

#endif

#ifdef DEBUG

void	debug_parsing(t_env *env)
{
	printf("\n\n********* DEBUG RESOLUTION *********\n\n");
	printf("resx	= %d\n", env->res.x);
	printf("resy	= %d\n", env->res.y);
	printf("\n\n********* DEBUG COLORS *********\n\n");
	printf("red_c   = %d\ngreen_c = %d\nblue_c  = %d\n",
				env->c.red, env->c.green, env->c.blue);
	printf("red_f   = %d\ngreen_f = %d\nblue_f  = %d\n",
				env->f.red, env->f.green, env->f.blue);
	printf("\n\n********* DEBUG PRINT TEXTURE *********\n\n");
	printf("path no : |%s|\n", env->tex.path_no);
	printf("path we : |%s|\n", env->tex.path_we);
	printf("path so : |%s|\n", env->tex.path_so);
	printf("path ea : |%s|\n", env->tex.path_ea);
	printf("path s : |%s|\n", env->tex.path_s);
	debug_print_map(env);
}

#else

void	debug_parsing(t_env *env)
{
	(void)env;
	return ;
}

#endif

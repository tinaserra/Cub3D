/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:32:40 by vserra            #+#    #+#             */
/*   Updated: 2021/02/17 19:29:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef DEBUG
void	debug_colors(t_env *env, int ctrl)
{
	printf("\n\n********* DEBUG COLORS *********\n\n");
	if (ctrl == 'C' || ctrl == 'B')
	{
		printf("red_c   = %d\n", env->col.red_c);
		printf("green_c = %d\n", env->col.green_c);
		printf("blue_c  = %d\n", env->col.blue_c);
	}
	if (ctrl == 'F' || ctrl == 'B')
	{
		printf("red_f   = %d\n", env->col.red_f);
		printf("green_f = %d\n", env->col.green_f);
		printf("blue_f  = %d\n", env->col.blue_f);
	}
}
#else
void	debug_colors(t_env *env, int ctrl)
{
	(void)env;
	(void)ctrl;
	return ;
}
#endif

#ifdef DEBUG
void	debug_size_map(t_env *env)
{
	printf("\n\n********* DEBUG SIZE MAP *********\n\n");
	printf("nb_lines = %d\n", env->map.map.nb_lines);
	printf("len_line = %d\n", env->len_line);
}
#else
void	debug_size_map(t_env *env)
{
	(void)env;
	return ;
}
#endif

#ifdef DEBUG
void	debug_resolution(t_env *env)
{
	printf("\n\n********* DEBUG RESOLUTION *********\n\n");
	printf("resx	= %d\n", env->res.x);
	printf("resy	= %d\n", env->res.y);
}
#else
void	debug_resolution(t_env *env)
{
	(void)env;
	return ;
}
#endif

#ifdef DEBUG
void	debug_print_map(t_env *env)
{
	int i;
	int j;

	printf("\n\n********* DEBUG PRINT MAP *********\n\n");
	printf("Player position = %c\n\n", env->player.orient_start);
	printf("-------------\n|    MAP    |\n-------------\n");
	i = 0;
	while (i < env->map.map.nb_lines)
	{
		j = 0;
		while (env->map.map[i][j] != '\0')
		{
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
	debug_resolution(env);
	debug_colors(env, 'B');
	debug_size_map(env);
	debug_print_map(env);
}
#else
void	debug_parsing(t_env *env)
{
	(void)env;
	return ;
}
#endif
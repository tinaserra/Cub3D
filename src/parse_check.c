/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:01:52 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:50:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_after_map(char *str, t_env *env)
{
	while (str[env->i])
	{
		if (str[env->i] != ' ')
			print_error(env, MAP_CHAR_AFTER);
		env->i++;
	}
	return (0);
}

int		check_element(t_env *env)
{
	if (env->res.x == -1)
		print_error(env, RESOLUTION);
	if (env->tex.path_no == NULL)
		print_error(env, EMPTY_NO);
	if (env->tex.path_ea == NULL)
		print_error(env, EMPTY_EA);
	if (env->tex.path_so == NULL)
		print_error(env, EMPTY_SO);
	if (env->tex.path_we == NULL)
		print_error(env, EMPTY_WE);
	if (env->tex.path_s == NULL)
		print_error(env, EMPTY_S);
	if (env->col.blue_f == -1)
		print_error(env, F_COLOR);
	if (env->col.blue_c == -1)
		print_error(env, C_COLOR);
	return (0);
}

int		check_color(t_env *env, int ctrl)
{
	if (ctrl == 'C')
	{
		if (env->col.red_c == -1 || env->col.green_c == -1 || env->col.blue_c == -1)
			print_error(env, C_COLOR);
	}
	if (ctrl == 'F')
	{
		if (env->col.red_f == -1 || env->col.green_f == -1 || env->col.blue_f == -1)
			print_error(env, F_COLOR);
	}
	return (0);
}

int	check_strend(char *str, t_env *env, int ctrl)
{
	while (str[env->i])
	{
		if (str[env->i] != ' ')
		{
			if (str[env->i] >= '0' && str[env->i] <= '9')
				print_error(env, MORE_NUM);
			if (ctrl == 'F')
			{
				env->col.blue_f = -1;
				print_error(env, F_COLOR_END);
			}
			if (ctrl == 'C')
			{
				env->col.blue_c = -1;
				print_error(env, C_COLOR_END);
			}
			if (ctrl == 'R')
			{
				env->res.x = -1;
				print_error(env, RESOLUTION_END);
			}
		}
		env->i++;
	}
	return (0);
}
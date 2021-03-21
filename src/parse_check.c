/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:01:52 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 14:03:39 by vserra           ###   ########.fr       */
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
	if (env->f.blue == -1)
		print_error(env, F_COLOR);
	if (env->c.blue == -1)
		print_error(env, C_COLOR);
	return (0);
}

int		check_color(t_env *env, int ctrl)
{
	if (ctrl == 'C')
	{
		if (env->c.red == -1 || env->c.green == -1 || env->c.blue == -1)
			print_error(env, C_COLOR);
	}
	if (ctrl == 'F')
	{
		if (env->f.red == -1 || env->f.green == -1 || env->f.blue == -1)
			print_error(env, F_COLOR);
	}
	return (0);
}

int		check_strend(char *str, t_env *env, int ctrl)
{
	while (str[env->i])
	{
		if (str[env->i] != ' ')
		{
			if (str[env->i] >= '0' && str[env->i] <= '9')
				print_error(env, MORE_NUM);
			if (ctrl == 'F')
			{
				env->f.blue = -1;
				print_error(env, F_COLOR_END);
			}
			if (ctrl == 'C')
			{
				env->c.blue = -1;
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

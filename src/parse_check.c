/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:01:52 by vserra            #+#    #+#             */
/*   Updated: 2021/02/17 19:28:47 by vserra           ###   ########.fr       */
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
	// if (env->path_no == NULL)
	// 	ft_putstr_fd("Error :\n[NO] is wrong or not specified\n", 1);
	// if (env->ea == -1)
	// 	ft_putstr_fd("Error :\n[EA] is wrong or not specified\n", 1);
	// if (env->so == -1)
	// 	ft_putstr_fd("Error :\n[SO] is wrong or not specified\n", 1);
	// if (env->we == -1)
	// 	ft_putstr_fd("Error :\n[WE] is wrong or not specified\n", 1);
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
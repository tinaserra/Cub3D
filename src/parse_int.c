/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:56 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:52:07 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		bb_atoi(char *str, t_env *env)
{
	int			len;
	long long	nbr;

	len = 0;
	nbr = -1;
	while (str[env->i] == ' ')
		env->i++;
	if (str[env->i] && str[env->i] >= '0' && str[env->i] <= '9')
		nbr = 0;
	while (str[env->i] && str[env->i] >= '0' && str[env->i] <= '9' && len < 11)
	{
		nbr = nbr * 10 + (str[env->i] - '0');
		env->i++;
		len++;
	}
	if (nbr > INT_MAX)
		nbr = -1;
	return (nbr);
}

// while ((str[env->i] >= 9 && str[env->i] <= 13) || str[env->i] == ' ')

void	get_c_color(char* str, t_env *env)
{
	if (env->col.red_c != -1) // Check le double element C
		print_error(env, DOUBLE_COLOR);
	if (str[env->i])
	{
		env->i++;
		env->col.red_c = bb_atoi(str, env);
		while (str[env->i] == ' ')
			env->i++;
		if ((env->col.red_c > -1 && env->col.red_c < 256) && str[env->i] == ',')
		{
			env->i++;
			env->col.green_c = bb_atoi(str, env);
			while (str[env->i] == ' ')
				env->i++;
			if (env->col.green_c < 256 && str[env->i] == ',')
			{
				env->i++;
				env->col.blue_c = bb_atoi(str, env);
			}
		}
		if (env->col.blue_c > 255)
			env->col.blue_c = -1;
		// debug_colors(env, 'C');
		check_strend(str, env, 'C');
	}
	check_color(env, 'C');
}

void	get_f_color(char* str, t_env *env)
{
	if (env->col.red_f != -1) // Check le double element F
		print_error(env, DOUBLE_COLOR);
	if (str[env->i])
	{
		env->i++;
		env->col.red_f = bb_atoi(str, env);
		while (str[env->i] == ' ')
			env->i++;
		if ((env->col.red_f > -1 && env->col.red_f < 256) && str[env->i] == ',')
		{
			env->i++;
			env->col.green_f = bb_atoi(str, env);
			while (str[env->i] == ' ')
				env->i++;
			if (env->col.green_f < 256 && str[env->i] == ',')
			{
				env->i++;
				env->col.blue_f = bb_atoi(str, env);
			}
		}
		if (env->col.blue_f > 255)
			env->col.blue_f = -1;
		// debug_colors(env, 'F');
		check_strend(str, env, 'F');
	}
	check_color(env, 'F');
}

void	get_resolution(char *str, t_env *env)
{
	if (env->res.x != -1) // Check le double element R
		print_error(env, DOUBLE_RESOLUTION);
	if (str[env->i])
	{
		env->i++;
		if ((env->res.x = bb_atoi(str, env)) == -1)
			print_error(env, RESOLUTION);
		if ((env->res.y = bb_atoi(str, env)) == -1)
			print_error(env, RESOLUTION);
		// debug_resolution(env);
		check_strend(str, env, 'R');
	}
}
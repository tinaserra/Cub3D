/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:56 by vserra            #+#    #+#             */
/*   Updated: 2021/03/22 13:11:00 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	bb_atoi(char *str, t_env *env)
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

void		get_c_color(char *str, t_env *env)
{
	if (env->c.red != -1)
		print_error(env, DOUBLE_COLOR);
	if (str[env->i])
	{
		env->i++;
		env->c.red = bb_atoi(str, env);
		while (str[env->i] == ' ')
			env->i++;
		if ((env->c.red > -1 && env->c.red < 256) && str[env->i] == ',')
		{
			env->i++;
			env->c.green = bb_atoi(str, env);
			while (str[env->i] == ' ')
				env->i++;
			if (env->c.green < 256 && str[env->i] == ',')
			{
				env->i++;
				env->c.blue = bb_atoi(str, env);
			}
		}
		if (env->c.blue > 255)
			env->c.blue = -1;
		check_strend(str, env, 'C');
	}
	check_color(env, 'C');
}

void		get_f_color(char *str, t_env *env)
{
	if (env->f.red != -1)
		print_error(env, DOUBLE_COLOR);
	if (str[env->i])
	{
		env->i++;
		env->f.red = bb_atoi(str, env);
		while (str[env->i] == ' ')
			env->i++;
		if ((env->f.red > -1 && env->f.red < 256) && str[env->i] == ',')
		{
			env->i++;
			env->f.green = bb_atoi(str, env);
			while (str[env->i] == ' ')
				env->i++;
			if (env->f.green < 256 && str[env->i] == ',')
			{
				env->i++;
				env->f.blue = bb_atoi(str, env);
			}
		}
		if (env->f.blue > 255)
			env->f.blue = -1;
		check_strend(str, env, 'F');
	}
	check_color(env, 'F');
}

void		get_resolution(char *str, t_env *env)
{
	if (env->res.x != -1)
		print_error(env, DOUBLE_RESOLUTION);
	if (str[env->i])
	{
		env->i++;
		if ((env->res.x = bb_atoi(str, env)) == -1)
			print_error(env, RESOLUTION);
		if ((env->res.y = bb_atoi(str, env)) == -1)
			print_error(env, RESOLUTION);
		if (env->res.x == 0 || env->res.y == 0)
			print_error(env, RESOLUTION);
		check_strend(str, env, 'R');
	}
}

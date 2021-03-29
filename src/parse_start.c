/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2021/03/22 13:33:55 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map(char *file, t_env *env)
{
	int		fd;
	int		ret;
	int		i;

	ret = 1;
	env->line = NULL;
	fd = open(file, O_RDONLY);
	if (!(env->map.map = malloc(sizeof(char*) * env->map.nb_lines)))
		print_error(env, MALLOC_FAILED);
	i = -1;
	while (++i < env->map.nb_lines)
		env->map.map[i] = NULL;
	while (ret != 0)
	{
		ret = get_next_line(env, fd, &env->line);
		if (env->line[0] != '\0' && is_a_map(env->line) == 0)
			dup_map(env->line, env);
		free(env->line);
		env->line = NULL;
	}
	close(fd);
	if (env->ply.orient_start == 'o')
		print_error(env, NO_PLAYER);
	check_walls(env);
	return (0);
}

static void	get_size_map(char *str, t_env *env)
{
	int len;

	env->i = 0;
	len = -1;
	if (env->map.end_map == 1)
		check_after_map(str, env);
	while (str[env->i] && str[env->i] == ' ')
		env->i++;
	if ((str[0] != '\0') && (is_char_map(str, env) == 0))
	{
		check_element(env);
		env->map.nb_lines++;
		len = ft_strlen(str);
		if (len > env->map.len_line)
			env->map.len_line = len;
	}
	if (env->map.len_line == 1)
		print_error(env, MAP_INCOMPLETE);
}

static int	get_elements(char *str, t_env *env)
{
	env->i = 0;
	while (str[env->i] == ' ')
		env->i++;
	if (str[env->i] == 'R')
		get_resolution(str, env);
	else if (str[env->i] == 'F')
		get_f_color(str, env);
	else if (str[env->i] == 'C')
		get_c_color(str, env);
	else if (str[env->i] == 'N' && str[env->i + 1] == 'O')
		env->tex.path_no = get_path(str, env->i + 2, env);
	else if (str[env->i] == 'W' && str[env->i + 1] == 'E')
		env->tex.path_we = get_path(str, env->i + 2, env);
	else if (str[env->i] == 'S' && str[env->i + 1] == 'O')
		env->tex.path_so = get_path(str, env->i + 2, env);
	else if (str[env->i] == 'E' && str[env->i + 1] == 'A')
		env->tex.path_ea = get_path(str, env->i + 2, env);
	else if (str[env->i] == 'S')
		env->tex.path_s = get_path(str, env->i + 1, env);
	else
		return (-1);
	return (0);
}

void		parsing(char *file, t_env *env)
{
	int		fd;
	int		ret;

	ret = 1;
	env->line = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		print_error(env, CUB_DIR);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(env, CUB_INVALIDE);
	while (ret != 0)
	{
		ret = get_next_line(env, fd, &env->line);
		if (get_elements(env->line, env) == -1)
			get_size_map(env->line, env);
		if (env->line[0] == '\0' && env->map.nb_lines != 0)
			env->map.end_map = 1;
		free(env->line);
		env->line = NULL;
	}
	close(fd);
	if (env->map.nb_lines == 0)
		print_error(env, NO_MAP);
	get_map(file, env);
	debug_parsing(env);
}

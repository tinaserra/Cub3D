/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:59:46 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:53:49 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check :
// pas d'espaces dans le path
// double element
// il peut y avoir des espaces avant et apres
// s'il y a une erreur (malloc failes ou double element il faut free)

void	check_double_texture(char *str, t_env *env)
{
	if (str[env->i] == 'N' && env->tex.path_no != NULL)
		print_error(env, DOUBLE_NO);
	if (str[env->i] == 'E' && env->tex.path_ea != NULL)
		print_error(env, DOUBLE_EA);
	if (str[env->i] == 'W' && env->tex.path_we != NULL)
		print_error(env, DOUBLE_WE);
	if (str[env->i] == 'S' && str[env->i + 1] == 'O'
		&& env->tex.path_so != NULL)
		print_error(env, DOUBLE_SO);
	if (str[env->i] == 'S' && str[env->i + 1] != 'O'
		&& env->tex.path_s != NULL)
		print_error(env, DOUBLE_S);
}

	// printf("path : |%s|\n", path);
char	*get_path(char *str, int i, t_env *env)
{
	int		len;
	int		c;
	char	*path;

	check_double_texture(str, env);
	len = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + len] && str[i + len] != ' ')
		len++;
	path = malloc(len + 1);
	if (path == NULL)
		print_error(env, MALLOC_FAILED);
	c = 0;
	while (c < len)
	{
		path[c] = str[i + c];
		c++;
	}
	path[len] = '\0';
	return (path);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:59:46 by vserra            #+#    #+#             */
/*   Updated: 2021/02/11 16:16:37 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check :
// pas d'espaces dans le path
// double element
// il peut y avoir des espaces avant et apres
// s'il y a une erreur (malloc failes ou double element il faut free)

void	check_double_texture(char *str, t_parsing *parse)
{
	if (str[parse->i] == 'N' && parse->path_no != NULL)
		print_error(parse, DOUBLE_NO);
	if (str[parse->i] == 'E' && parse->path_ea != NULL)
		print_error(parse, DOUBLE_EA);
	if (str[parse->i] == 'W' && parse->path_we != NULL)
		print_error(parse, DOUBLE_WE);
	if (str[parse->i] == 'S' && str[parse->i + 1] == 'O'
		&& parse->path_so != NULL)
		print_error(parse, DOUBLE_SO);
	if (str[parse->i] == 'S' && str[parse->i + 1] != 'O'
		&& parse->path_s != NULL)
		print_error(parse, DOUBLE_S);
}

char	*get_path(char *str, int i, t_parsing *parse)
{
	int		len;
	int		c;
	char	*path;

	check_double_texture(str, parse);
	len = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + len] && str[i + len] != ' ')
		len++;
	path = malloc(len + 1);
	if (path == NULL)
		print_error(parse, MALLOC_FAILED);
	c = 0;
	while (c < len)
	{
		path[c] = str[i + c];
		c++;
	}
	path[len] = '\0';
	// printf("path : |%s|\n", path);
	return (path);
}
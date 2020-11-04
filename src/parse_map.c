/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:42:56 by vserra            #+#    #+#             */
/*   Updated: 2020/11/04 18:20:34 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		player_position(t_parsing *parse, char c, int i, int j) // Static
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (parse->player.orient_start == 'o')
		{
			parse->player.orient_start = c;
			parse->player.px = i;
			parse->player.py = j;
			return (0);
		}
		else
			map_error(parse, MULTI_PLAYER);
	}
	return (-1);
}

int		dup_map(char *str, t_parsing *parse)
{
	static int	i = 0;
	int			j;

	j = 0;
	parse->map[i] = NULL;
	if (!(parse->map[i] = malloc(sizeof(char) * parse->len_line + 1)))
		free_error(parse, MALLOC_FAILED); // A MODIF
	while (str[j] != '\0')
	{
		if (player_position(parse, str[j], i, j) == 0)
			parse->map[i][j] = '0';
		else if (str[j] == ' ')
			parse->map[i][j] = '.';
		else
			parse->map[i][j] = str[j];
		j++;
	}
	while (j < parse->len_line)
	{
		parse->map[i][j] = '.';
		j++;
	}
	parse->map[i][j] = '\0';
	i++;
	return (0);
}

int		is_char_map(char *str, t_parsing *parse, int ctrl)
{
	while (str[parse->i])
	{
		while (str[parse->i] == ' ')
			parse->i++;
		if (str[parse->i] != '1' && str[parse->i] != ' ' && str[parse->i] != '0' 
			&& str[parse->i] != '2' && str[parse->i] != 'N' && str[parse->i] != 'S'
			&& str[parse->i] != 'E' && str[parse->i] != 'W' && str[parse->i])
			{
				if (ctrl == 1)
					map_error(parse, MAP_WRONG_CHAR);
				if (ctrl == 2)
				{
					// ft_putstr_fd("Cette ligne n'est pas une map\n", 1); // pas une erreur
					return (-1);
				}
			}
		parse->i++;
	}
	return (0);
}

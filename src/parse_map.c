/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:42:56 by vserra            #+#    #+#             */
/*   Updated: 2021/02/04 12:17:58 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		player_position(t_parsing *parse, char c, int i, int j) // Static
{
	// printf("str[j] = %c\n", c);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (parse->player.orient_start == 'o')
		{
			parse->player.orient_start = c;
			parse->player.px = i + 0.5; // se positioner au centre de la case
			parse->player.py = j + 0.5;
			if (c == 'N')
				parse->player.dirX = -1; // vecteur de direction initiale (commence à -1 pour N, 1 pour S, 0 sinon)
			if (c == 'E')
				parse->player.dirY = 1;
			if (c == 'S')
				parse->player.dirX = 1;
			if (c == 'W')
				parse->player.dirY = -1;
			return (0);
		}
		else
			print_error(parse, MULTI_PLAYER);
	}
	// printf("Player position = %c\n\n", parse->player.orient_start);
	return (-1);
}

int		dup_map(char *str, t_parsing *parse)
{
	static int	y = 0;
	int			x;

	x = 0;
	parse->map[y] = NULL;
	if (!(parse->map[y] = malloc(sizeof(char) * parse->len_line + 1)))
		print_error(parse, MALLOC_FAILED);
	while (str[x] != '\0')
	{
		if (player_position(parse, str[x], y, x) == 0)
			parse->map[y][x] = '0';
		else if (str[x] == ' ')
			parse->map[y][x] = '.'; // remplace des espaces par des 1 !
		else
			parse->map[y][x] = str[x];
		x++;
	}
	while (x < parse->len_line)
	{
		parse->map[y][x] = '.';
		x++;
	}
	parse->map[y][x] = '\0';
	y++;
	return (0);
}

int		is_a_map(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '0' 
			&& str[i] != '2' && str[i] != 'N' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'W' && str[i])
			return (-1);
		i++;
	}
	return (0);
}

int		is_char_map(char *str, t_parsing *parse)
{
	while (str[parse->i])
	{
		if (str[parse->i] != '1' && str[parse->i] != ' ' && str[parse->i] != '0'
			&& str[parse->i] != '2' && str[parse->i] != 'N' && str[parse->i] != 'S'
			&& str[parse->i] != 'E' && str[parse->i] != 'W' && str[parse->i])
			{
				print_error(parse, MAP_WRONG_CHAR);
			}
		parse->i++;
	}
	return (0);
}

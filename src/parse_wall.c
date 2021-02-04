/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2021/02/04 12:08:58 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_borders(t_parsing *parse)
{
	int x;
	int y;
	// first colonne & last colonne
	y = 0;
	x = 0;
	while (y < parse->nb_lines)
	{
		if (parse->map[y][0] != '1' && parse->map[y][0] != '.')
			print_error(parse, MAP_WALL);
		if (parse->map[y][parse->len_line - 1] != '1'
			&& parse->map[y][parse->len_line - 1] != '.')
			print_error(parse, MAP_WALL);
		y++;
	}
	// first line & last line
	while (x < parse->len_line)
	{
		if (parse->map[0][x] != '1' && parse->map[0][x] != '.')
			print_error(parse, MAP_WALL);
		if (parse->map[parse->nb_lines - 1][x] != '1'
			&& parse->map[parse->nb_lines - 1][x] != '.')
			print_error(parse, MAP_WALL);
		x++;
	}
}

void	check_spaces(t_parsing *parse, int x, int y)
{
	// ligne au dessus
	if (y != 0 && x != 0 && parse->map[y - 1][x - 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
	if (y != 0 && parse->map[y - 1][x] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
	if (y != 0 && x != parse->len_line && parse->map[y - 1][x + 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
	// return ;

	// ligne
	if (x != 0 && parse->map[y][x - 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
	if (x != parse->len_line && parse->map[y][x + 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}

	// ligne en dessous
	if (y != parse->len_line && x != 0 && parse->map[y + 1][x - 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
	if (y != parse->len_line && parse->map[y + 1][x] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
	if (y != parse->len_line && x != parse->len_line
		&& parse->map[y + 1][x + 1] == '.')
	{
		printf("x = %d, y = %d\n", x , y);
		print_error(parse, MAP_WALL);
	}
}

void	check_walls(t_parsing *parse)
{
	int x;
	int y;

	y = 0;
	debug_print_map(parse);
	while (y < parse->nb_lines)
	{
		x = 0;
		while (x < parse->len_line) // parse->nb_lines
		{
			if (parse->map[y][x] == '0' || parse->map[y][x] == '2')
			{
				check_spaces(parse, x, y);
			}
			x++;
		}
		y++;
	}
}

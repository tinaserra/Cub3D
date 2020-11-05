/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2020/11/05 14:22:58 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_top_left_angle(t_parsing *parse, int i, int j)
{
	if (i != parse->nb_lines - 1 && j != 0)
	{
		if ((parse->map[i + 1][j] == '0' || parse->map[i + 1][j] == '2') &&
			parse->map[i + 1][j - 1] == '1' && parse->map[i][j - 1] != '1')
			{
				printf("line %d : [WRONG] angle haut gauche pas ferme\n", i + 5);
				map_error(parse, MAP_WALL);
			}
	}
}

void check_bot_left_angle(t_parsing *parse, int i, int j)
{
	if (i != 0 && j != 0)
	{
		if ((parse->map[i - 1][j] == '0' || parse->map[i - 1][j] == '2') &&
			parse->map[i - 1][j - 1] == '1' && parse->map[i][j - 1] != '1')
			{
				printf("line %d : [WRONG] angle bas gauche pas ferme\n", i + 5);
				map_error(parse, MAP_WALL);
			}
	}
}

void check_top_right_angle(t_parsing *parse, int i, int j)
{
	if (i != parse->nb_lines - 1 && j != parse->nb_lines - 1)
	{
		if ((parse->map[i + 1][j] == '0' || parse->map[i + 1][j] == '2') &&
			parse->map[i + 1][j + 1] == '1' && parse->map[i][j + 1] != '1')
			{
				printf("line %d : [WRONG] angle haut droit pas ferme\n", i + 5);
				map_error(parse, MAP_WALL);
			}
	}
}

void check_bot_right_angle(t_parsing *parse, int i, int j)
{
	if (i != 0 && j != parse->len_line - 1)
	{
		if ((parse->map[i - 1][j] == '0' || parse->map[i - 1][j] == '2') &&
			parse->map[i - 1][j + 1] == '1' && parse->map[i][j + 1] != '1')
			{
				printf("line %d : [WRONG] angle bas droit pas ferme\n", i + 5);
				map_error(parse, MAP_WALL);
			}
	}
}

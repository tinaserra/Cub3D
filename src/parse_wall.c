/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2020/11/05 14:01:22 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_top_left_angle(t_parsing *parse, int i, int j)
{
	// check en dessous
	if (i != parse->nb_lines - 1 && j != 0)
	{
		if ((parse->map[i + 1][j] == '0' || parse->map[i + 1][j] == '2') &&
			parse->map[i + 1][j - 1] == '1' && parse->map[i][j - 1] != '1')
			{
				printf("line %d : [WRONG] angle haut gauche pas ferme\n", i + 5);
				map_error(parse, MAP_WALL);
			}
	}
	// ft_putstr_fd("[OK] angle haut droit ferme\n", 1);
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
	// ft_putstr_fd("[OK] angle bas droit ferme\n", 1);
}

void check_top_right_angle(t_parsing *parse, int i, int j)
{
	// check en dessous
	if (i != parse->nb_lines - 1 && j != parse->nb_lines - 1)
	{
		if ((parse->map[i + 1][j] == '0' || parse->map[i + 1][j] == '2') &&
			parse->map[i + 1][j + 1] == '1' && parse->map[i][j + 1] != '1')
			{
				printf("line %d : [WRONG] angle haut droit pas ferme\n", i + 5);
				map_error(parse, MAP_WALL);
			}
	}
	// ft_putstr_fd("[OK] angle haut droit ferme\n", 1);
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
	// ft_putstr_fd("[OK] angle bas droit ferme\n", 1);
}

void	wall_in_col(t_parsing *parse)
{
	int row;
	int col;

	col = 0;
	while (col < parse->len_line)
	{
		row = 0;
		while (parse->map[row][col] == '.')
			row++;
		if (parse->map[row][col] != '1')
			map_error(parse, MAP_WALL);
		// printf("Mur trouvé G ---- ");
		check_top_left_angle(parse, row, col);
		check_top_right_angle(parse, row, col);

		row = parse->nb_lines - 1;
		while (parse->map[row][col] == '.')
			row--;
		if (parse->map[row][col] != '1')
			map_error(parse, MAP_WALL);
		// printf("Mur trouvé D\n");
		check_bot_left_angle(parse, row, col);
		check_bot_right_angle(parse, row, col);
		col++;
	}
	return ;
}

void	wall_in_row(t_parsing *parse)
{
	int row;
	int col;

	row = 0;
	while (row < parse->nb_lines)
	{
		col = 0;
		while (parse->map[row][col] == '.')
			col++;
		if (parse->map[row][col] != '1')
			map_error(parse, MAP_WALL);
		// printf("Mur trouvé G ---- ");
		check_top_left_angle(parse, row, col);
		check_bot_left_angle(parse, row, col);

		col = parse->len_line - 1;
		while (parse->map[row][col] == '.')
			col--;
		if (parse->map[row][col] != '1')
			map_error(parse, MAP_WALL);
		// printf("Mur trouvé D\n");
		check_top_right_angle(parse, row, col);
		check_bot_right_angle(parse, row, col);
		row++;
	}
	return ;
}
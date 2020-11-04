/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2020/11/04 19:19:43 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_left_angle(t_parsing *parse, int i, int j)
{
	// check en dessous
	if (i != parse->nb_lines - 1 && j != 0)
	{
		if ((parse->map[i + 1][j] == '0' || parse->map[i + 1][j] == '2') &&
			parse->map[i + 1][j + 1] == '1' && parse->map[i][j + 1] != '1')
			{
				printf("line %d : [WRONG] angle haut gauche pas ferme\n", i + 5);
				return ;
			}
	}
	// ft_putstr_fd("[OK] angle haut droit ferme\n", 1);
	if (i != 0 - 1 && j != parse->len_line - 1)
	{
		if ((parse->map[i - 1][j] == '0' || parse->map[i - 1][j] == '2') &&
			parse->map[i - 1][j + 1] == '1' && parse->map[i][j + 1] != '1')
			{
				printf("line %d : [WRONG] angle bas gauche pas ferme\n", i + 5);
				return ;
			}
	}
	// ft_putstr_fd("[OK] angle bas droit ferme\n", 1);
}

void check_right_angle(t_parsing *parse, int i, int j)
{
	// check en dessous
	if (i != parse->nb_lines - 1 && j != 0)
	{
		if ((parse->map[i + 1][j] == '0' || parse->map[i + 1][j] == '2') &&
			parse->map[i + 1][j - 1] == '1' && parse->map[i][j - 1] != '1')
			{
				printf("line %d : [WRONG] angle haut droit pas ferme\n", i + 5);
				return ;
			}
	}
	// ft_putstr_fd("[OK] angle haut droit ferme\n", 1);
	if (i != 0 - 1 && j != parse->len_line - 1)
	{
		if ((parse->map[i - 1][j] == '0' || parse->map[i - 1][j] == '2') &&
			parse->map[i - 1][j - 1] == '1' && parse->map[i][j - 1] != '1')
			{
				printf("line %d : [WRONG] angle bas droit pas ferme\n", i + 5);
				return ;
			}
	}
	// ft_putstr_fd("[OK] angle bas droit ferme\n", 1);
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
		check_right_angle(parse, row, col);

		col = parse->len_line - 1;
		while (parse->map[row][col] == '.')
			col--;
		if (parse->map[row][col] != '1')
			map_error(parse, MAP_WALL);
		// printf("Mur trouvé D\n");
		check_left_angle(parse, row, col);
		row++;
	}
	return ;
}
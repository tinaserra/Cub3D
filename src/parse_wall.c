/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:47:22 by vserra            #+#    #+#             */
/*   Updated: 2020/11/04 17:47:43 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_in_row(t_parsing *parse)
{
	int row;
	int col;

	row = 0;
		printf("\n\nlen line %d\n", parse->len_line);
		printf("nb lines %d\n\n", parse->nb_lines);
	while (row < parse->nb_lines)
	{
		col = 0;
		while (parse->map[row][col] == '.')
			col++;
		if (parse->map[row][col] != '1')
		{
			//error;
			printf("Map not close\n");
			return ;
		}
		printf("Mur trouvé G ---- ");
		// else -> check angles

		col = parse->len_line - 1;
		while (parse->map[row][col] == '.')
			col--;
		if (parse->map[row][col] != '1')
		{
			//error;
			printf("Map not close\n");
			return ;
		}
		printf("Mur trouvé D\n");
		// else -> check angles
		row++;
	}
	return ;
}
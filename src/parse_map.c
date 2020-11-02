/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:42:56 by vserra            #+#    #+#             */
/*   Updated: 2020/11/02 12:15:11 by tinaserra        ###   ########.fr       */
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
			print_error(parse, MULTI_PLAYER);
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
			parse->map[i][j] = '1';
		else
			parse->map[i][j] = str[j];
		j++;
	}
	while (j < parse->len_line)
	{
		parse->map[i][j] = '1';
		j++;
	}
	parse->map[i][j] = '\0';
	i++;
	return (0);
}

		// if ((str[parse->i] < 9 && str[parse->i] > 13) || str[parse->i] != 32)
		// (str[parse->i] != '\t' && str[parse->i] != '\n' && str[parse->i] != '\r'
		//	&& str[parse->i] != '\v' && str[parse->i] != '\f' && str[parse->i] != ' ')
int		check_after_map(char *str, t_parsing *parse)
{
	while (str[parse->i])
	{
		if (str[parse->i] != ' ')
			print_error(parse, MAP_CHAR_AFTER);
		parse->i++;
	}
	return (0);
}

int		check_element(t_parsing *parse)
{
	// if (parse->col.blue_c == -1 || parse->col.blue_f == -1 || parse->resx == -1
	// 	|| parse->no == -1 || parse->ea == -1 || parse->so == -1 || parse->we == -1)
	if (parse->resx == -1)
		print_error(parse, RESOLUTION);
	// if (parse->no == -1)
	// 	ft_putstr_fd("Error :\n[NO] is wrong or not specified\n", 1);
	// if (parse->ea == -1)
	// 	ft_putstr_fd("Error :\n[EA] is wrong or not specified\n", 1);
	// if (parse->so == -1)
	// 	ft_putstr_fd("Error :\n[SO] is wrong or not specified\n", 1);
	// if (parse->we == -1)
	// 	ft_putstr_fd("Error :\n[WE] is wrong or not specified\n", 1);
	if (parse->col.blue_f == -1)
		print_error(parse, F_COLOR);
	if (parse->col.blue_c == -1)
	{
		print_error(parse, C_COLOR);
		// return (-1);
	}
	return (0);
}

int		is_char_map(char *str, t_parsing *parse)
{
	while (str[parse->i])
	{
		while (str[parse->i] == ' ')
			parse->i++;
		if (str[parse->i] != '1' && str[parse->i] != ' ' && str[parse->i] != '0' 
			&& str[parse->i] != '2' && str[parse->i] != 'N' && str[parse->i] != 'S'
			&& str[parse->i] != 'E' && str[parse->i] != 'W' && str[parse->i])
			{
				// ft_putstr_fd("Cette ligne n'est pas une map\n", 1); // pas une erreur
				return (-1);
			}
		parse->i++;
	}
	return (0);
}

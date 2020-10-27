/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:42:56 by vserra            #+#    #+#             */
/*   Updated: 2020/10/24 11:19:22 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_after_map(char *str, t_parsing *parse)
{
	while (str[parse->i])
	{
		if (str[parse->i] != '\t' || str[parse->i] != '\n' || str[parse->i] != '\r'
			|| str[parse->i] != '\v' || str[parse->i] != '\f' || str[parse->i] != ' ')
		// if ((str[parse->i] < 9 && str[parse->i] > 13) || str[parse->i] != 32)
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
			while ((str[parse->i] >= 9 && str[parse->i] <= 13) || str[parse->i] == 32)
				parse->i++;
			if (str[parse->i] != '1' && str[parse->i] != ' ' && str[parse->i] != '0' 
				&& str[parse->i] != '2' && str[parse->i] != 'N' && str[parse->i] != 'S'
				&& str[parse->i] != 'E' && str[parse->i] != 'W' && str[parse->i])
				{
					// ft_putstr_fd("Cette ligne n'est pas une map\n", 1);
					return (-1);
				}
			parse->i++;
		}
	return (0);
}

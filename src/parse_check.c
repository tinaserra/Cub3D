/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:01:52 by vserra            #+#    #+#             */
/*   Updated: 2020/11/04 13:55:37 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_is_map(char *str, t_parsing *parse)
{
	while (str[parse->i])
	{
		while (str[parse->i] == ' ')
			parse->i++;
		if (str[parse->i] != '1' && str[parse->i] != ' ' && str[parse->i] != '0' 
			&& str[parse->i] != '2' && str[parse->i] != 'N' && str[parse->i] != 'S'
			&& str[parse->i] != 'E' && str[parse->i] != 'W' && str[parse->i])
			{
				ft_putstr_fd("*** Wrong char in map ***\n", 1); // pas une erreur
				// return (-1);
				exit(EXIT_FAILURE);
			}
		parse->i++;
	}
	return (0);
}

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

int		check_color(t_parsing *parse, int ctrl)
{
	if (ctrl == 'C')
	{
		if (parse->col.red_c == -1 || parse->col.green_c == -1 || parse->col.blue_c == -1)
			print_error(parse, C_COLOR);
	}
	if (ctrl == 'F')
	{
		if (parse->col.red_f == -1 || parse->col.green_f == -1 || parse->col.blue_f == -1)
			print_error(parse, F_COLOR);
	}
	return (0);
}

// if ((str[parse->i] < 9 && str[parse->i] > 13) || str[parse->i] != ' ')
int	check_strend(char *str, t_parsing *parse, int ctrl)
{
	while (str[parse->i])
	{
		if (str[parse->i] != ' ')
		{
			if (str[parse->i] >= '0' && str[parse->i] <= '9')
				print_error(parse, MORE_NUM);
			if (ctrl == 'F')
			{
				parse->col.blue_f = -1;
				print_error(parse, F_COLOR_END);
			}
			if (ctrl == 'C')
			{
				parse->col.blue_c = -1;
				print_error(parse, C_COLOR_END);
			}
			if (ctrl == 'R')
			{
				parse->resx = -1;
				print_error(parse, RESOLUTION_END);
			}
		}
		parse->i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:56 by vserra            #+#    #+#             */
/*   Updated: 2020/11/02 13:49:08 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// while (str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
//			|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' ')
int		bb_atoi(char *str, t_parsing *parse)
{
	int			len;
	long long	nbr;

	len = 0;
	nbr = -1;
	while (str[parse->i] == ' ')
		parse->i++;
	if (str[parse->i] && str[parse->i] >= '0' && str[parse->i] <= '9')
		nbr = 0;
	while (str[parse->i] && str[parse->i] >= '0' && str[parse->i] <= '9' && len < 11)
	{
		nbr = nbr * 10 + (str[parse->i] - '0');
		parse->i++;
		len++;
	}
	if (nbr > INT_MAX)
		nbr = -1;
	return (nbr);
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

// while ((str[parse->i] >= 9 && str[parse->i] <= 13) || str[parse->i] == ' ')

void	get_c_color(char* str, t_parsing *parse)
{
	if (parse->col.red_c != -1) // Check le double element C
		print_error(parse, DOUBLE_ELEMENT);
	if (str[parse->i])
	{
		parse->i++;
		parse->col.red_c = bb_atoi(str, parse);
		while (str[parse->i] == ' ')
			parse->i++;
		if ((parse->col.red_c > -1 && parse->col.red_c < 256) && str[parse->i] == ',')
		{
			parse->i++;
			parse->col.green_c = bb_atoi(str, parse);
			while (str[parse->i] == ' ')
				parse->i++;
			if (parse->col.green_c < 256 && str[parse->i] == ',')
			{
				parse->i++;
				parse->col.blue_c = bb_atoi(str, parse);
			}
		}
		if (parse->col.blue_c > 255)
			parse->col.blue_c = -1;
		// debug_colors(parse, 'C');
		check_strend(str, parse, 'C');
	}
	check_color(parse, 'C');
}

void	get_f_color(char* str, t_parsing *parse)
{
	if (parse->col.red_f != -1) // Check le double element F
		print_error(parse, DOUBLE_ELEMENT);
	if (str[parse->i])
	{
		parse->i++;
		parse->col.red_f = bb_atoi(str, parse);
		while (str[parse->i] == ' ')
			parse->i++;
		if ((parse->col.red_f > -1 && parse->col.red_f < 256) && str[parse->i] == ',')
		{
			parse->i++;
			parse->col.green_f = bb_atoi(str, parse);
			while (str[parse->i] == ' ')
				parse->i++;
			if (parse->col.green_f < 256 && str[parse->i] == ',')
			{
				parse->i++;
				parse->col.blue_f = bb_atoi(str, parse);
			}
		}
		if (parse->col.blue_f > 255)
			parse->col.blue_f = -1;
		// debug_colors(parse, 'F');
		check_strend(str, parse, 'F');
	}
	check_color(parse, 'F');
}

void	get_resolution(char *str, t_parsing *parse)
{
	if (parse->resx != -1) // Check le double element R
		print_error(parse, DOUBLE_ELEMENT);
	if (str[parse->i])
	{
		parse->i++;
		if ((parse->resx = bb_atoi(str, parse)) == -1)
			print_error(parse, RESOLUTION);
		if ((parse->resy = bb_atoi(str, parse)) == -1)
			print_error(parse, RESOLUTION);
		// debug_resolution(parse);
		check_strend(str, parse, 'R');
	}
}
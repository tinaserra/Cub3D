/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:56 by vserra            #+#    #+#             */
/*   Updated: 2020/10/23 16:43:33 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		bb_atoi(char *str, t_parsing *parse)
{
	int			len;
	long long	nbr;

	len = 0;
	nbr = -1;
	while (str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
			|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' ')
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
		{
			ft_putstr_fd("Error :\n[C] Wrong color\n", 1);
			return (-1);
		}
	}
	if (ctrl == 'F')
	{
		if (parse->col.red_f == -1 || parse->col.green_f == -1 || parse->col.blue_f == -1)
		{
			ft_putstr_fd("Error :\n[F] Wrong color\n", 1);
			return (-1);
		}
	}
	return (0);
}

int	check_strend(char *str, t_parsing *parse, int ctrl)
{
	while (str[parse->i])
	{
		if ((str[parse->i] < 9 && str[parse->i] > 13) || str[parse->i] != 32)
		{
		// if (str[parse->i] && str[parse->i] >= '0' && str[parse->i] <= '9')
		// 	ft_putstr_fd("Error :\nMore than 3 numbers\n", 1);
		// else
			if (ctrl == 'F')
			{
				ft_putstr_fd("Error :\n[F] Wrong caracter at the end\n", 1);
				parse->col.blue_f = -1;
				return (-1);
			}
			if (ctrl == 'C')
			{
				ft_putstr_fd("Error :\n[C] Wrong caracter at the end\n", 1);
				parse->col.blue_f = -1;
				return (-1);
			}
			if (ctrl == 'R')
			{
				ft_putstr_fd("Error :\n[R] Wrong caracter at the end\n", 1);
				parse->resx = -1;
				return (-1);
			}
		}
		parse->i++;
	}
	return (0);
}

int		get_c_color(char* str, t_parsing *parse)
{
	int ret;

	ret = 0;
	if (parse->col.red_c != -1) // Check le double element C
		return (-1);
	if (str[parse->i])
	{
		parse->i++;
		parse->col.red_c = bb_atoi(str, parse);
		while ((str[parse->i] >= 9 && str[parse->i] <= 13) || str[parse->i] == 32)
			parse->i++;
		if ((parse->col.red_c > -1 && parse->col.red_c < 256) && str[parse->i] == ',')
		{
			parse->i++;
			parse->col.green_c = bb_atoi(str, parse);
			while ((str[parse->i] >= 9 && str[parse->i] <= 13) || str[parse->i] == 32)
				parse->i++;
			if (parse->col.green_c < 256 && str[parse->i] == ',')
			{
				parse->i++;
				parse->col.blue_c = bb_atoi(str, parse);
			}
		}
		if (parse->col.blue_c > 255)
			parse->col.blue_c = -1;
		printf("R = %d\n", parse->col.red_c);
		printf("G = %d\n", parse->col.green_c);
		printf("B = %d\n", parse->col.blue_c);
		// ret = check_strend(str, parse, 'C');
		return (check_strend(str, parse, 'C'));
	}
	ret = check_color(parse, 'C');
	printf("ret = %d\n", ret);
	return (ret);
}

int		get_f_color(char* str, t_parsing *parse)
{
	int ret;

	ret = 0;
	if (parse->col.red_f != -1) // Check le double element F
		return (-1);
	if (str[parse->i])
	{
		parse->i++;
		parse->col.red_f = bb_atoi(str, parse);
		while ((str[parse->i] >= 9 && str[parse->i] <= 13) || str[parse->i] == 32)
			parse->i++;
		if ((parse->col.red_f > -1 && parse->col.red_f < 256) && str[parse->i] == ',')
		{
			parse->i++;
			parse->col.green_f = bb_atoi(str, parse);
			while ((str[parse->i] >= 9 && str[parse->i] <= 13) || str[parse->i] == 32)
				parse->i++;
			if (parse->col.green_f < 256 && str[parse->i] == ',')
			{
				parse->i++;
				parse->col.blue_f = bb_atoi(str, parse);
			}
		}
		if (parse->col.blue_f > 255)
			parse->col.blue_f = -1;
		printf("R = %d\n", parse->col.red_f);
		printf("G = %d\n", parse->col.green_f);
		printf("B = %d\n", parse->col.blue_f);
		// ret = check_strend(str, parse, 'F');
		return (check_strend(str, parse, 'F'));
	}
	ret = check_color(parse, 'F');
	printf("ret = %d\n", ret);
	return (ret); // 0
}

int		get_resolution(char *str, t_parsing *parse)
{
	int ret;

	ret = 0;

	if (parse->resx != -1) // Check le double element R
		return (-1);
	if (str[parse->i])
	{
		parse->i++;
		if ((parse->resx = bb_atoi(str, parse)) == -1)
			// ft_putstr_fd("Error :\n[R] -> Wrong resolution\n", 1); //Wrong input for resolution
			return (-1);
		if ((parse->resy = bb_atoi(str, parse)) == -1)
			// ft_putstr_fd("Error :\n[R] -> Wrong resolution\n", 1); //Wrong input for resolution
			return (-1);
		printf("resx = %d\n", parse->resx);
		printf("resy = %d\n", parse->resy);
		ret = check_strend(str, parse, 'R');
	}
	return (ret);
}
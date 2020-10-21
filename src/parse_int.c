#include "cub3d.h"

void	init_color(t_parsing *parse)
{
	parse->col.red_f = -1;
	parse->col.green_f = -1;
	parse->col.blue_f = -1;

	parse->col.red_c = -1;
	parse->col.green_c = -1;
	parse->col.blue_c = -1;
}

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

int		check_color(int red, int green, int blue)
{
	if (red == -1 || green == -1 || blue == -1)
	{
		ft_putstr_fd("Error :\nWrong color\n", 1);
		return (-1);
	}
	return (0);
}

int	check_strend(char *str, t_parsing *parse)
{
	while (str[parse->i])
	{
	// if (!(str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
	// 	|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' '))
	if ((str[parse->i] < 9 && str[parse->i] > 13) && str[parse->i] != 32)
	{
		if (str[parse->i] && str[parse->i] >= '0' && str[parse->i] <= '9')
			ft_putstr_fd("Error :\nMore than 3 numbers\n", 1);
		else
			ft_putstr_fd("Error :\nWrong caracter at the end\n", 1);
		return (-1);
	}
		parse->i++;
	}
	return (0);
}

int		get_c_color(char* str, t_parsing *parse)
{
	int ret;

	ret = 0;
	if (parse->col.red_c != -1)
		return (-1);
	if (str[parse->i])
	{
		parse->i++;
		parse->col.red_c = bb_atoi(str, parse);
		while ((str[parse->i] >= 9 && str[parse->i] <= 13) && str[parse->i] == 32)
			parse->i++;
		if ((parse->col.red_c < -1 || parse->col.red_c < 256) && str[parse->i] == ',')
		{
			parse->i++;
			parse->col.green_c = bb_atoi(str, parse);
			while ((str[parse->i] >= 9 && str[parse->i] <= 13) && str[parse->i] == 32)
				parse->i++;
			if (parse->col.green_c < 256 && str[parse->i] == ',')
			{
				parse->i++;
				parse->col.blue_c = bb_atoi(str, parse);
			}
		}
		printf("R = %d\n", parse->col.red_c);
		printf("G = %d\n", parse->col.green_c);
		printf("B = %d\n", parse->col.blue_c);
		if (parse->col.blue_c > 255)
			parse->col.blue_c = -1;
		ret = check_strend(str, parse);
	}
	ret = check_color(parse->col.red_c, parse->col.green_c, parse->col.blue_c);
	return (ret);
}

int		get_f_color(char* str, t_parsing *parse)
{
	int ret;

	ret = 0;
	if (parse->col.red_f != -1)
		return (-1);
	if (str[parse->i])
	{
		parse->i++;
		parse->col.red_f = bb_atoi(str, parse);
		while ((str[parse->i] >= 9 && str[parse->i] <= 13) && str[parse->i] == 32)
			parse->i++;
		if ((parse->col.red_f < -1 || parse->col.red_f < 256) && str[parse->i] == ',')
		{
			parse->i++;
			parse->col.green_f = bb_atoi(str, parse);
			while ((str[parse->i] >= 9 && str[parse->i] <= 13) && str[parse->i] == 32)
				parse->i++;
			if (parse->col.green_f < 256 && str[parse->i] == ',')
			{
				parse->i++;
				parse->col.blue_f = bb_atoi(str, parse);
			}
		}
		printf("R = %d\n", parse->col.red_f);
		printf("G = %d\n", parse->col.green_f);
		printf("B = %d\n", parse->col.blue_f);
		if (parse->col.blue_f > 255)
			parse->col.blue_f = -1;
		ret = check_strend(str, parse);
	}
	else
	ret = check_color(parse->col.red_f, parse->col.green_f, parse->col.blue_f);
	return (ret);
}

int		get_resolution(char *str, t_parsing *parse)
{
	int ret;

	ret = 0;
	parse->resx = 0;
	parse->resy = 0;

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
		ret = check_strend(str, parse);
	}
	return (ret);
}
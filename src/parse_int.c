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

int		get_color(char* str, t_parsing *parse)
{
	parse->parse_color.red_f = -1;
	parse->parse_color.green_f = -1;
	parse->parse_color.blue_f = -1;

	parse->i++;
	if (str[parse->i])
	{
		parse->parse_color.red_f = bb_atoi(str, parse);
		while (str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
				|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' ')
			parse->i++;
		if (str[parse->i] == ',')
		{
			parse->i++;
			parse->parse_color.green_f = bb_atoi(str, parse);
			while (str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
					|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' ')
				parse->i++;
			if (str[parse->i] == ',')
			{
				parse->i++;
				parse->parse_color.blue_f = bb_atoi(str, parse);
			}
		}
	}
	printf("R = %d\n", parse->parse_color.red_f);
	printf("G = %d\n", parse->parse_color.green_f);
	printf("B = %d\n", parse->parse_color.blue_f);
		while (str[parse->i])
		{
			// CHECK AFTER
			while (!(str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
				|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' '))
			{
				if (str[parse->i] && str[parse->i] >= '0' && str[parse->i] <= '9')
					ft_putstr_fd("Error :\nMore than 3 numbers\n", 1);
				else
					ft_putstr_fd("Error :\nWrong caracter at the end\n", 1);
				parse->i++;
				return (-1);
			}
			parse->i++;
	}
	return (0);
}

int		get_resolution(char *str, t_parsing *parse)
{
	parse->resx = 0;
	parse->resy = 0;

	parse->i++;
	while (str[parse->i])
	{
		if (parse->resx == 0)
		{
			if ((parse->resx = bb_atoi(str, parse)) == -1)
			{
				ft_putstr_fd("Error :\nWrong input for\n", 1); //Wrong input for resolution
				// return (-1);
			}
			printf("resx = %d\n", parse->resx);
		}
		if (parse->resy == 0)
		{
			if ((parse->resy = bb_atoi(str, parse)) == -1)
			{
				ft_putstr_fd("Error :\nWrong caracter\n", 1); //Wrong input for resolution
				// return (-1);
			}
			printf("resy = %d\n", parse->resy);
		}
		// CHECK AFTER
		while (!(str[parse->i] == '\t' || str[parse->i] == '\n' || str[parse->i] == '\r'
			|| str[parse->i] == '\v' || str[parse->i] == '\f' || str[parse->i] == ' '))
		{
			if (str[parse->i] && str[parse->i] >= '0' && str[parse->i] <= '9')
				ft_putstr_fd("Error :\nMore than 2 numbers\n", 1);
			else
				ft_putstr_fd("Error :\nWrong caracter at the end\n", 1);
			parse->i++;
			return (-1);
		}
		parse->i++;
	}
	return (0);
}
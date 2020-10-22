/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2020/10/22 11:40:13 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
** /!\ aux espaces
** /!\ aux lignes vides
*/

	// ft_putstr_fd("OKKKK\n", 1);

int     parsing_elements(char *str, t_parsing *parse)
{
	parse->i = 0;

	if (str[parse->i] == '\0')
		return (0);
	while (str[parse->i] == ' ')
		parse->i++;
	if (str[parse->i] == 'R')
	{
		// ft_putstr_fd("c'est R resolution\n", 1);
		get_resolution(str, parse);
	}
	if (str[parse->i] == 'F')
	{
		// ft_putstr_fd("c'est F sol\n", 1);
		get_f_color(str, parse);
	}
	if (str[parse->i] == 'C')
	{
		// ft_putstr_fd("c'est C plafond\n", 1);
		get_c_color(str, parse);
	}
	if (str[parse->i] == 'N' && str[parse->i + 1] == 'O')
		ft_putstr_fd("c'est texture (NO)\n", 1);
	if (str[parse->i] == 'W' && str[parse->i + 1] == 'E')
		ft_putstr_fd("c'est texture (WE)\n", 1);
	if (str[parse->i] == 'S' && str[parse->i + 1] == 'O')
		ft_putstr_fd("c'est texture (SO)\n", 1);
	if (str[parse->i] == 'E' && str[parse->i + 1] == 'A')
		ft_putstr_fd("c'est texture (EA)\n", 1);
	if (str[parse->i] == 'S' && str[parse->i + 1] != 'O')
		ft_putstr_fd("c'est S sprite\n", 1);
	return (0);
}

void	parsing(char *file, t_parsing *parse)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		ft_putstr_fd("ERROR : Invalide : is a directory\n", 1); // ft_error(parse, "Invalide : is a directory\n");
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_putstr_fd("ERROR : Invalide : file .cub invalide\n", 1); // ft_error(parse, "file .cub invalide\n");
	init_color(parse);
	while (ret != 0)
	{
		ft_putstr_fd("\n- ON VA LIRE\n", 1);
		ret = get_next_line(fd, &str);
		printf("ligne = %s\n", str);
		parsing_elements(str, parse);
		// parse_map(str, parse);
		free(str);
	}
	close(fd);
	// if (parse->sizeline == 0 || parse->nblines == 0)
	// 	ft_error(parse, "Map absente\n");
	// ft_parsing_map(file, parse);
}

int		check_file_name(char *file, t_parsing *parse)
{
	printf("arg = %s\n", file);

	int			i;

	i = 0;
	while (file[i])
		i++;
	if (file[0] == '.' || (file[i - 4] != '.' && file[i - 3] != 'c' && file[i - 2] != 'u' && file[i - 1] != 'b'))
	{
		ft_putstr_fd("ERROR : Invalide name map\n", 1);
		return (-1);
	}
	parsing(file, parse);
	return (0);
}

// int			ft_printf(const char *str, ...)
// {
// 	int		i;
// 	t_data	data;

// 	i = 0;
// 	data.format = (unsigned char *)str;

// 	va_start(data.ap, str);

// 	parsing(&data);
// 	va_end(data.ap);
// 	return (data.nb_char);
// }

int main(int argc, char **argv)
{
	t_parsing parse;

	(void)argc;

	check_file_name(argv[1], &parse);
}
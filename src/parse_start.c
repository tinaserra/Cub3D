/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2020/10/24 10:52:12 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** /!\ aux espaces
** /!\ aux lignes vides
*/

// int		get_size_map(char *str, t_parsing *parse)
// {
// 	(void)str;

// 	parse->i = 0;
// 	return (0);
// }

int     get_elements(char *str, t_parsing *parse)
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
		print_error(parse, CUB_DIR);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(parse, CUB_INVALIDE);
	while (ret != 0)
	{
		// ft_putstr_fd("\n- ON VA LIRE\n", 1);
		ret = get_next_line(fd, &str);
		// printf("ligne = %s\n", str);
		get_elements(str, parse);
		get_size_map(str, parse);
		free(str);
	}
	close(fd);
	debug_resolution(parse);
	debug_colors(parse, 'B');
	debug_size_map(parse);
	// if (parse->sizeline == 0 || parse->nblines == 0)
	// 	ft_error(parse, "Map absente\n");
	// ft_parsing_map(file, parse);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2020/11/05 14:09:32 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// (ft_strchr(str, '1') != NULL)

int		get_map(char *file, t_parsing *parse)
{
	int fd;
	int ret;
	char *str;

	ret = 1;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (!(parse->map = malloc(sizeof(char*) * parse->nb_lines)))
		free_error(parse, MALLOC_FAILED);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		// printf("str = |%s|\n", str);
		if ((str[0] != '\0') && (is_char_map(str, parse, 2) == 0))
			dup_map(str, parse);
		free(str);
	}
	close(fd);
	if (parse->player.orient_start == 'o')
		map_error(parse, NO_PLAYER);
	wall_in_row(parse);
	wall_in_col(parse);
	// ft_init_sprite(parse);
	// debug_print_map(parse);
	return (0);
}

void	get_size_map(char *str, t_parsing *parse)
{
	int len;

	parse->i = 0;
	len = -1;
	if(parse->end_map == 1)
		check_after_map(str, parse);
	if ((str[0] != '\0') && (is_char_map(str, parse, 1) == 0))
	{
		// ft_putstr_fd("Cette ligne est une map\n", 1);
		check_element(parse);
		if (parse->nb_lines == -1) // init nb_lines a 0 pour virer ces deux lignes
			parse->nb_lines++;
		parse->nb_lines++;
		len = ft_strlen(str);
		if (len > parse->len_line)
			parse->len_line = len;
	}
	if (parse->nb_lines == 1 || parse->len_line == 1) // la map fait une ligne
			map_error(parse, MAP_INCOMPLETE);
	// debug_size_map(parse);
}

int		get_elements(char *str, t_parsing *parse)
{
	parse->i = 0;

	while (str[parse->i] == ' ')
		parse->i++;
	if (str[parse->i] == 'R')
		get_resolution(str, parse);
	if (str[parse->i] == 'F')
		get_f_color(str, parse);
	if (str[parse->i] == 'C')
		get_c_color(str, parse);
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
	if (str[parse->i] != '\0')
	{
		// pas un element
		return (-1);
	}
	return (0);
}

void	parsing(char *file, t_parsing *parse)
{
	int fd;
	int ret;
	char *str;

	ret = 1;
	str = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		file_error(parse, CUB_DIR);
	if ((fd = open(file, O_RDONLY)) == -1)
		file_error(parse, CUB_INVALIDE);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		// printf("\n\n* ligne = |%s| ---------- *\n", str);
		if (get_elements(str, parse) == -1)
			get_size_map(str, parse);
		if (str[0] == '\0' && parse->nb_lines != -1) // Check apres map
			parse->end_map = 1;
		free(str);
	}
	close(fd);
	if (parse->nb_lines == -1)
		map_error(parse, NO_MAP);
	get_map(file, parse);
	// debug_parsing(parse);
	debug_print_map(parse);
}

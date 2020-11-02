/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2020/11/02 14:08:34 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if ((ft_strchr(str, '1') != NULL) && (is_char_map(str, parse)) == 0)
			dup_map(str, parse);
		free(str);
	}
	close(fd);
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
	if (str[parse->i] == '\0' && parse->nb_lines != -1) // Check apres map
		parse->end_map = 1;
	if ((ft_strchr(str, '1') != NULL) && (is_char_map(str, parse)) == 0)
	{
		// ft_putstr_fd("\nCette ligne est une map\n", 1);
		check_element(parse);
		if (parse->nb_lines == -1)
			parse->nb_lines++;
		parse->nb_lines++;
		len = ft_strlen(str);
		if (len > parse->len_line)
			parse->len_line = len;
	}
	// debug_size_map(parse);
}

void	get_elements(char *str, t_parsing *parse)
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
}

void	parsing(char *file, t_parsing *parse)
{
	int fd;
	int ret;
	char *str;

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
	if (parse->nb_lines == -1)
		print_error(parse, NO_MAP);
	get_map(file, parse);
	debug_parsing(parse);
}

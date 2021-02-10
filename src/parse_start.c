/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2021/02/10 17:21:00 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// printf("str = |%s|\n", str);

int		get_map(char *file, t_parsing *parse)
{
	int fd;
	int ret;
	char *str;

	ret = 1;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (!(parse->map = malloc(sizeof(char*) * parse->nb_lines)))
		print_error(parse, MALLOC_FAILED);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		// parse->i = 0; // useless ?
		// while (str[parse->i] == ' ')
		// parse->i++;
		if (str[0] != '\0' && is_a_map(str) == 0)
			dup_map(str, parse);
		free(str);
	}
	close(fd);
	if (parse->player.px == 'o')
		print_error(parse, NO_PLAYER);
	check_borders(parse);
	check_walls(parse);
	return (0);
}

void	get_size_map(char *str, t_parsing *parse)
{
	int len;

	parse->i = 0;
	len = -1;
	if(parse->end_map == 1)
		check_after_map(str, parse);
	while (str[parse->i] && str[parse->i] == ' ')
		parse->i++;
	if ((str[0] != '\0') && (is_char_map(str, parse) == 0)) //check que les char de la map soient good
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
	if (parse->len_line == 1) // la map fait une ligne parse->nb_lines == 1
		print_error(parse, MAP_INCOMPLETE);
}

int		get_elements(char *str, t_parsing *parse)
{
	parse->i = 0;

	while (str[parse->i] == ' ')
		parse->i++;
	if (str[parse->i] == 'R')
		get_resolution(str, parse);
	else if (str[parse->i] == 'F')
		get_f_color(str, parse);
	else if (str[parse->i] == 'C')
		get_c_color(str, parse);
	else if (str[parse->i] == 'N' && str[parse->i + 1] == 'O')
		parse->path_no = get_texture(str, 2, parse);
	else if (str[parse->i] == 'W' && str[parse->i + 1] == 'E')
		parse->path_we = get_texture(str, 2, parse);
	else if (str[parse->i] == 'S' && str[parse->i + 1] == 'O')
		parse->path_so = get_texture(str, 2, parse);
	else if (str[parse->i] == 'E' && str[parse->i + 1] == 'A')
		parse->path_ea = get_texture(str, 2, parse);
	else if (str[parse->i] == 'S')
		parse->path_s = get_texture(str, 1, parse);
	else
	{
		// ft_putstr_fd("cette ligne n'est pas un element\n", 1);
		return (-1);
	}
	return (0);
}

void	parsing(char *file, t_env *env)
{
	int fd;
	int ret;
	char *str;

	ret = 1;
	str = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		print_error(&env->parse, CUB_DIR);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(&env->parse, CUB_INVALIDE);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		// printf("\n\n* ligne = |%s| ---------- *\n", str);
		if (get_elements(str, &env->parse) == -1)
			get_size_map(str, &env->parse);
		if (str[0] == '\0' && env->parse.nb_lines != -1) // Check apres map
			env->parse.end_map = 1;
		free(str);
	}
	close(fd);
	if (env->parse.nb_lines == -1)
		print_error(&env->parse, NO_MAP);
	get_map(file, &env->parse);
	debug_parsing(&env->parse);
	// debug_print_map(&env->parse);
	start_mlx(env);
}

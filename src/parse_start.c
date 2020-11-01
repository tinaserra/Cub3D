/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:05 by vserra            #+#    #+#             */
/*   Updated: 2020/10/28 16:01:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		player_position(t_parsing *parse, char c, int i, int j)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (parse->player.orient_start == 'o')
		{
			parse->player.orient_start = c;
			parse->player.px = i;
			parse->player.py = j;
			return (0);
		}
		else
			print_error(parse, MULTI_PLAYER);
	}
	// printf("player position = %c\n", parse->player.orient_start);
	return (-1);
}

int		dup_map(char *str, t_parsing *parse)
{
	static int	i = 0;
	int			j;

	j = 0;
	parse->map[i] = NULL;
	if (!(parse->map[i] = malloc(sizeof(char) * parse->len_line + 1)))
		free_error(parse, MALLOC_FAILED); // A MODIF
	while (str[j] != '\0')
	{
		if (player_position(parse, str[j], i, j) == 0)
			parse->map[i][j] = '0';
		else if (str[j] == ' ')
			parse->map[i][j] = '1';
		else
			parse->map[i][j] = str[j];
		j++;
	}
	while (j <= (parse->len_line - 1))
	{
		parse->map[i][j] = '1';
		j++;
	}
	parse->map[i][j] = '\0';
	i++;
	return (0);
}

int		get_map(char *fichier, t_parsing *parse)
{
	int			fd;
	int			ret;
	int			lines;
	char		*str;
	int i = 0;
	int j = 0;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	lines = parse->nb_lines;
	printf("nb lines = %d\n", lines);
	if (!(parse->map = malloc(sizeof(char*) * parse->nb_lines)))
		free_error(parse, MALLOC_FAILED);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		// if (parse->insidemap == 1 && ft_lignevide(str) == 0 &&
		// 		parse->count < parse->nblines)
		// 	parse->lignevide = 1;
		printf("line1 = %s\n", str);
		if ((ft_strchr(str, '1') != NULL) && (is_char_map(str, parse)) == 0)
		{
			// parse->count++;
			while (lines > 0)
			{
				dup_map(str, parse);
				printf("line2 = %s\n", str);
				printf("nb lines = %d\n", lines);
				lines--;
			}
		}
		free(str);
	}
	close(fd);
	// ft_init_sprite(parse);
	while (i < parse->nb_lines)
	{
		while (j < parse->len_line)
		{
			printf("%c", parse->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

void	get_size_map(char *str, t_parsing *parse)
{
	int			len;

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

	if (str[parse->i] == '\0') // Useless ?
		return ;
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
	if (parse->nb_lines == -1)
		print_error(parse, NO_MAP);
	get_map(file, parse);
}

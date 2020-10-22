/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:13:49 by vserra            #+#    #+#             */
/*   Updated: 2020/10/22 17:40:28 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_file_name(char *file, t_parsing *parse)
{
	int			i;

	i = 0;
	while (file[i])
		i++;
	if (file[0] == '.' || (file[i - 4] != '.' && file[i - 3] != 'c'
		&& file[i - 2] != 'u' && file[i - 1] != 'b'))
	{
		ft_putstr_fd("ERROR : Invalide name map\n", 1);
		return (-1);
	}
	parsing(file, parse);
	return (0);
}

int		main(int argc, char **argv)
{
	t_parsing parse;

	(void)argc;
	init_parse(&parse);
	check_file_name(argv[1], &parse);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:13:49 by vserra            #+#    #+#             */
/*   Updated: 2021/01/14 14:26:45 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_file_name(char *file, t_parsing *parse)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[0] == '.' || (file[i - 4] != '.' && file[i - 3] != 'c'
		&& file[i - 2] != 'u' && file[i - 1] != 'b'))
		file_error(parse, FILE_NAME);
	parsing(file, parse);
	return (0);
}

// 2 args -> nom du programme & fichier.cub
// 3 args -> nom du programme & fichier.cub & --save

int		main(int ac, char **av)
{
	t_parsing parse;

	// (void)argc;
	init_parse(&parse);
	if (ac == 2 || ac == 3) // && check_save(argv[2]) == 1))
	{
		if (ac == 3) // argument save
			parse.save = 1;
		check_file_name(av[1], &parse);
	}
	else
		write(1, "Error\nArguments invalides\n", 30);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:13:49 by vserra            #+#    #+#             */
/*   Updated: 2021/03/17 15:17:54 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_save(char *save)
{
	int	i;

	i = 0;
	while (save[i])
		i++;
	if (save[i - 1] == 'e' && save[i - 2] == 'v' && save[i - 3] == 'a' &&
		save[i - 4] == 's' && save[i - 5] == '-' && save[i - 6] == '-'
		&& ft_strlen(save) < 7)
		return (0);
	return (-1);
}

static int	check_file_name(char *file, t_env *env)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[0] == '.' || (file[i - 4] != '.' && file[i - 3] != 'c'
		&& file[i - 2] != 'u' && file[i - 1] != 'b'))
		print_error(env, FILE_NAME);
	return (0);
}

/*
** 2 args -> nom du programme & fichier.cub
** 3 args -> nom du programme & fichier.cub & --save
*/

int			main(int ac, char **av)
{
	t_env env;

	ft_bzero(&env, sizeof(t_env));
	init_parse(&env);
	if (ac == 2 || (ac == 3 && check_save(av[2]) == 0))
	{
		if (ac == 3)
			env.save = 1;
		check_file_name(av[1], &env);
		parsing(av[1], &env);
		start_mlx(&env);
	}
	else
		print_error(&env, ARGS);
		// write(2, "Error\nInvalid arguments\n", 30);
	return (0);
}

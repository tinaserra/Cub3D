/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:46:03 by vserra            #+#    #+#             */
/*   Updated: 2021/02/11 18:04:20 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	quit(t_parsing *parse)
// {
// 	exit(EXIT_FAILURE);
// }

void	free_textures(t_parsing *parse)
{
	if (parse->path_no != NULL)
		free(parse->path_no);
	if (parse->path_ea != NULL)
		free(parse->path_ea);
	if (parse->path_so != NULL)
		free(parse->path_so);
	if (parse->path_we != NULL)
		free(parse->path_we);
	if (parse->path_s != NULL)
		free(parse->path_s);
}

void	free_map(t_parsing *parse)
{
	int		i;

	i = 0;
	while (parse->map[i])
	{
		// if (parse->map[i] != NULL)
		free(parse->map[i]);
		i++;
	}
	free(parse->map);
}

int print_error(t_parsing *parse, int error)
{
	free_textures(parse);
	if (parse->map != NULL)
		free_map(parse);
	ft_putstr_fd(g_str_error[error], 2);
	exit(EXIT_FAILURE);
}

// print_error(parse, RESOLUTION);

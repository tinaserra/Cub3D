/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:49:57 by vserra            #+#    #+#             */
/*   Updated: 2020/10/22 16:50:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse(t_parsing *parse)
{
	*parse = (t_parsing){ 
                            .resx = -1,
                            .resy = -1,
                            .col.red_f = -1,
                            .col.green_f = -1,
                            .col.blue_f = -1,
                            .col.red_c = -1,
                            .col.green_c = -1,
                            .col.blue_c = -1
                        };
	// parse->col.red_f = -1;
	// parse->col.green_f = -1;
	// parse->col.blue_f = -1;

	// parse->col.red_c = -1;
	// parse->col.green_c = -1;
	// parse->col.blue_c = -1;

	// parse->resx = -1;
	// parse->resy = -1;
	printf("R = %d\n", parse->col.red_f);
	printf("G = %d\n", parse->col.green_f);
	printf("B = %d\n", parse->col.blue_f);
	printf("R = %d\n", parse->col.red_c);
	printf("G = %d\n", parse->col.green_c);
	printf("B = %d\n", parse->col.blue_c);
}
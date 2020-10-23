/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:32:40 by vserra            #+#    #+#             */
/*   Updated: 2020/10/23 17:58:19 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef DEBUG

void	debug_colors(t_parsing *parse, int ctrl)
{
	printf("\n\n********* DEBUG COLORS *********\n\n");
    if (ctrl == 'C' || ctrl == 'B')
    {
        printf("red_c   = %d\n", parse->col.red_c);
        printf("green_c = %d\n", parse->col.green_c);
        printf("blue_c  = %d\n", parse->col.blue_c);
    }
    if (ctrl == 'F' || ctrl == 'B')
    {
        printf("red_f   = %d\n", parse->col.red_f);
        printf("green_f = %d\n", parse->col.green_f);
        printf("blue_f  = %d\n", parse->col.blue_f);
    }
}

#else

void	debug_colors(t_parsing *parse, int ctrl)
{
	(void)parse;
    (void)ctrl;
	return ;
}

#endif

#ifdef DEBUG

void	debug_size_map(t_parsing *parse)
{
	printf("\n\n********* DEBUG SIZE MAP *********\n\n");
    printf("nb_lines = %d\n", parse->nb_lines);
	printf("len_line = %d\n", parse->len_line);
}

#else

void	debug_size_map(t_parsing *parse)
{
	(void)parse;
	return ;
}

#endif

#ifdef DEBUG

void	debug_resolution(t_parsing *parse)
{
	printf("\n\n********* DEBUG RESOLUTION *********\n\n");
    printf("resx    = %d\n", parse->resx);
	printf("resy    = %d\n", parse->resy);
}

#else

void	debug_resolution(t_parsing *parse)
{
	(void)parse;
	return ;
}

#endif
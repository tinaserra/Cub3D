/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/03/22 14:09:04 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->map.map[(int)(env->ply.x + env->ply.dirx * MSPEED)]\
			[(int)(env->ply.y)] == '0')
		env->ply.x += env->ply.dirx * MSPEED;
	if (env->map.map[(int)(env->ply.x)]\
			[(int)(env->ply.y + env->ply.diry * MSPEED)] == '0')
		env->ply.y += env->ply.diry * MSPEED;
}

void	go_back(t_env *env)
{
	if (env->map.map[(int)(env->ply.x - env->ply.dirx * MSPEED)]\
			[(int)(env->ply.y)] == '0')
		env->ply.x -= env->ply.dirx * MSPEED;
	if (env->map.map[(int)(env->ply.x)]\
			[(int)(env->ply.y - env->ply.diry * MSPEED)] == '0')
		env->ply.y -= env->ply.diry * MSPEED;
}

void	go_right(t_env *env)
{
	if (env->map.map[(int)(env->ply.x + env->ply.diry * (MSPEED))]\
			[(int)env->ply.y] == '0')
		env->ply.x += env->ply.diry * MSPEED;
	if (env->map.map[(int)env->ply.x]\
			[(int)(env->ply.y - env->ply.dirx * (MSPEED * 2))] == '0')
		env->ply.y -= env->ply.dirx * MSPEED;
}

void	go_left(t_env *env)
{
	if (env->map.map[(int)(env->ply.x - env->ply.diry * (MSPEED))]\
			[(int)env->ply.y] == '0')
		env->ply.x -= env->ply.diry * MSPEED;
	if (env->map.map[(int)env->ply.x]\
			[(int)(env->ply.y + env->ply.dirx * (MSPEED * 2))] == '0')
		env->ply.y += env->ply.dirx * MSPEED;
}

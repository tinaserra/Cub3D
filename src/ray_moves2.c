/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 19:20:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->map.map[(int)(env->ply.x + env->ply.dirx * env->ply.mspeed)]
			[(int)(env->ply.y)] == '0')
		env->ply.x += env->ply.dirx * env->ply.mspeed;
	if (env->map.map[(int)(env->ply.x)]
			[(int)(env->ply.y + env->ply.diry * env->ply.mspeed)] == '0')
		env->ply.y += env->ply.diry * env->ply.mspeed;
}

void	go_back(t_env *env)
{
	if (env->map.map[(int)(env->ply.x - env->ply.dirx * env->ply.mspeed)]
			[(int)(env->ply.y)] == '0')
		env->ply.x -= env->ply.dirx * env->ply.mspeed;
	if (env->map.map[(int)(env->ply.x)]
			[(int)(env->ply.y - env->ply.diry * env->ply.mspeed)] == '0')
		env->ply.y -= env->ply.diry * env->ply.mspeed;
}

void	go_right(t_env *env)
{
	if (env->map.map[(int)(env->ply.x + env->ply.diry * (env->ply.mspeed))]
			[(int)env->ply.y] == '0')
		env->ply.x += env->ply.diry * env->ply.mspeed;
	if (env->map.map[(int)env->ply.x]
			[(int)(env->ply.y - env->ply.dirx * (env->ply.mspeed * 2))] == '0')
		env->ply.y -= env->ply.dirx * env->ply.mspeed;
}

void	go_left(t_env *env)
{
	if (env->map.map[(int)(env->ply.x - env->ply.diry * (env->ply.mspeed))]
			[(int)env->ply.y] == '0')
		env->ply.x -= env->ply.diry * env->ply.mspeed;
	if (env->map.map[(int)env->ply.x]
			[(int)(env->ply.y + env->ply.dirx * (env->ply.mspeed * 2))] == '0')
		env->ply.y += env->ply.dirx * env->ply.mspeed;
}

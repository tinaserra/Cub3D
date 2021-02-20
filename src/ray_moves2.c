/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/02/20 10:58:09 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->map.map[(int)(env->ply.px + env->ply.dirx * env->ply.mspeed)][(int)(env->ply.py)] == '0')
		env->ply.px += env->ply.dirx * env->ply.mspeed;
	if (env->map.map[(int)(env->ply.px)][(int)(env->ply.py + env->ply.diry * env->ply.mspeed)] == '0')
		env->ply.py += env->ply.diry * env->ply.mspeed;
}

void	go_back(t_env *env)
{
	if (env->map.map[(int)(env->ply.px - env->ply.dirx * env->ply.mspeed)][(int)(env->ply.py)] == '0')
		env->ply.px -= env->ply.dirx * env->ply.mspeed;
	if (env->map.map[(int)(env->ply.px)][(int)(env->ply.py - env->ply.diry * env->ply.mspeed)] == '0')
		env->ply.py -= env->ply.diry * env->ply.mspeed;
}

void	go_right(t_env *env)
{
	if (env->map.map[(int)(env->ply.px + env->ply.diry * (env->ply.mspeed /** 2*/))][(int)env->ply.py] == '0')
		env->ply.px += env->ply.diry * env->ply.mspeed;
	if (env->map.map[(int)env->ply.px][(int)(env->ply.py - env->ply.dirx * (env->ply.mspeed * 2))] == '0')
		env->ply.py -= env->ply.dirx * env->ply.mspeed;
}

void	go_left(t_env *env)
{
	if (env->map.map[(int)(env->ply.px - env->ply.diry * (env->ply.mspeed /** 2*/))][(int)env->ply.py] == '0')
		env->ply.px -= env->ply.diry * env->ply.mspeed;
	if (env->map.map[(int)env->ply.px][(int)(env->ply.py + env->ply.dirx  * (env->ply.mspeed * 2))] == '0')
		env->ply.py += env->ply.dirx  * env->ply.mspeed;
}
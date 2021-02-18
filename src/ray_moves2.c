/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 10:55:27 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->map.map[(int)(env->player.px + env->player.dirx * env->player.mspeed)][(int)(env->player.py)] == '0')
		env->player.px += env->player.dirx * env->player.mspeed;
	if (env->map.map[(int)(env->player.px)][(int)(env->player.py + env->player.diry * env->player.mspeed)] == '0')
		env->player.py += env->player.diry * env->player.mspeed;
}

void	go_back(t_env *env)
{
	if (env->map.map[(int)(env->player.px - env->player.dirx * env->player.mspeed)][(int)(env->player.py)] == '0')
		env->player.px -= env->player.dirx * env->player.mspeed;
	if (env->map.map[(int)(env->player.px)][(int)(env->player.py - env->player.diry * env->player.mspeed)] == '0')
		env->player.py -= env->player.diry * env->player.mspeed;
}

void	go_right(t_env *env)
{
	if (env->map.map[(int)(env->player.px + env->player.diry * (env->player.mspeed /** 2*/))][(int)env->player.py] == '0')
		env->player.px += env->player.diry * env->player.mspeed;
	if (env->map.map[(int)env->player.px][(int)(env->player.py - env->player.dirx * (env->player.mspeed * 2))] == '0')
		env->player.py -= env->player.dirx * env->player.mspeed;
}

void	go_left(t_env *env)
{
	if (env->map.map[(int)(env->player.px - env->player.diry * (env->player.mspeed /** 2*/))][(int)env->player.py] == '0')
		env->player.px -= env->player.diry * env->player.mspeed;
	if (env->map.map[(int)env->player.px][(int)(env->player.py + env->player.dirx  * (env->player.mspeed * 2))] == '0')
		env->player.py += env->player.dirx  * env->player.mspeed;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/02/17 19:44:18 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->map.map[(int)(env->player.px + env->player.dirx * env->movespeed)][(int)(env->player.py)] == '0')
		env->player.px += env->player.dirx * env->movespeed;
	if (env->map.map[(int)(env->player.px)][(int)(env->player.py + env->player.diry * env->movespeed)] == '0')
		env->player.py += env->player.diry * env->movespeed;
}

void	go_back(t_env *env)
{
	if (env->map.map[(int)(env->player.px - env->player.dirx * env->movespeed)][(int)(env->player.py)] == '0')
		env->player.px -= env->player.dirx * env->movespeed;
	if (env->map.map[(int)(env->player.px)][(int)(env->player.py - env->player.diry * env->movespeed)] == '0')
		env->player.py -= env->player.diry * env->movespeed;
}
void	go_right(t_env *env)
{
	if (env->map.map[(int)(env->player.px + env->player.diry * (env->movespeed /** 2*/))][(int)env->player.py] == '0')
		env->player.px += env->player.diry * env->movespeed;
	if (env->map.map[(int)env->player.px][(int)(env->player.py - env->player.dirx * (env->movespeed * 2))] == '0')
		env->player.py -= env->player.dirx * env->movespeed;
}

void	go_left(t_env *env)
{
	if (env->map.map[(int)(env->player.px - env->player.diry * (env->movespeed /** 2*/))][(int)env->player.py] == '0')
		env->player.px -= env->player.diry * env->movespeed;
	if (env->map.map[(int)env->player.px][(int)(env->player.py + env->player.dirx  * (env->movespeed * 2))] == '0')
		env->player.py += env->player.dirx  * env->movespeed;
}

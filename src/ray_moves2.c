/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_moves2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:32 by vserra            #+#    #+#             */
/*   Updated: 2021/02/10 13:14:52 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_env *env)
{
	if (env->parse.map[(int)(env->parse.player.px + env->parse.player.dirX * env->moveSpeed)][(int)(env->parse.player.py)] == '0')
		env->parse.player.px += env->parse.player.dirX * env->moveSpeed;
	if (env->parse.map[(int)(env->parse.player.px)][(int)(env->parse.player.py + env->parse.player.dirY * env->moveSpeed)] == '0')
		env->parse.player.py += env->parse.player.dirY * env->moveSpeed;
}

void	go_back(t_env *env)
{
	if (env->parse.map[(int)(env->parse.player.px - env->parse.player.dirX * env->moveSpeed)][(int)(env->parse.player.py)] == '0')
		env->parse.player.px -= env->parse.player.dirX * env->moveSpeed;
	if (env->parse.map[(int)(env->parse.player.px)][(int)(env->parse.player.py - env->parse.player.dirY * env->moveSpeed)] == '0')
		env->parse.player.py -= env->parse.player.dirY * env->moveSpeed;
}
void	go_right(t_env *env)
{
	if (env->parse.map[(int)(env->parse.player.px + env->parse.player.dirY * (env->moveSpeed /** 2*/))][(int)env->parse.player.py] == '0')
		env->parse.player.px += env->parse.player.dirY * env->moveSpeed;
	if (env->parse.map[(int)env->parse.player.px][(int)(env->parse.player.py - env->parse.player.dirX * (env->moveSpeed * 2))] == '0')
		env->parse.player.py -= env->parse.player.dirX * env->moveSpeed;
}

void	go_left(t_env *env)
{
	if (env->parse.map[(int)(env->parse.player.px - env->parse.player.dirY * (env->moveSpeed /** 2*/))][(int)env->parse.player.py] == '0')
		env->parse.player.px -= env->parse.player.dirY * env->moveSpeed;
	if (env->parse.map[(int)env->parse.player.px][(int)(env->parse.player.py + env->parse.player.dirX  * (env->moveSpeed * 2))] == '0')
		env->parse.player.py += env->parse.player.dirX  * env->moveSpeed;
}

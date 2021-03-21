/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:16 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 09:42:16 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** HEADER
**
** La signature (sur 2 bytes), 'BM' indiquant qu'il s'agit d'un fichier BMP.
** BM, 424D en hexadécimal, indique qu'il s'agit d'un Bitmap Windows.
** write(fd, "BM", 2);
**
** La taille totale du fichier en bytes (codée sur 4 bytes).
** tmp = 14 + 40 + 4 * env->res.x * env->res.y;
**
** La largeur de l'image (sur 4 bytes) : le nombre de pixels horizontalement.
** write(fd, &env->res.x, 4);
**
** La hauteur de l'image (sur 4 bytes) : le nombre de pixels verticalemen.
** write(fd, &env->res.y, 4);
**
** Le nombre de plans (sur 2 bytes). Cette valeur vaut toujours 1.
** tmp = 1;
** write(fd, &tmp, 2);
**
** La profondeur de codage de la couleur(sur 2 bytes): le nombre de bits utilisé
** pour coder la couleur. Cette valeur peut être égale à 1, 4, 8, 16, 24 ou 32
** write(fd, &env->img.bits_per_pixel, 2);
**
** La méthode de compression (sur 4 bytes).
** Cette valeur vaut 0 lorsque l'image n'est pas compressée.
** tmp = 0;
** write(fd, &tmp, 4);
*/

void	header(t_env *env, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * env->res.x * env->res.y;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &env->res.x, 4);
	write(fd, &env->res.y, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &env->img.bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	save_bmp(t_env *env)
{
	int	fd;
	int	x;
	int	y;

	if ((fd = open("ta_gueule.bmp", O_CREAT | O_WRONLY, S_IRWXU)) == -1)
		print_error(env, BMP);
	header(env, fd);
	y = env->res.y;
	while (y >= 0)
	{
		x = 0;
		while (x < env->res.x)
		{
			write(fd, &env->img.data[y * (env->img.size_line / 4) + x], 4);
			x++;
		}
		y--;
	}
}

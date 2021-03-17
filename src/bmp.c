/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:16 by vserra            #+#    #+#             */
/*   Updated: 2021/03/17 15:27:46 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




void	header(t_env *env, int fd)
{
  int	tmp;

  write(fd, "BM", 2); //La signature (sur 2 octets), indiquant qu'il s'agit d'un fichier BMP à l'aide des deux caractères. 
  		    // BM, 424D en hexadécimal, indique qu'il s'agit d'un Bitmap Windows.
  tmp = 14 + 40 + 4 * env->res.x * env->res.y; //La taille totale du fichier en octets (codée sur 4 octets)
  write(fd, &tmp, 4);
  tmp = 0;
  write(fd, &tmp, 2); 
  write(fd, &tmp, 2); 
  tmp = 54;
  write(fd, &tmp, 4);
  tmp = 40;
  write(fd, &tmp, 4);
  write(fd, &env->res.x, 4); //La largeur de l'image (sur 4 octets), c'est-à-dire le nombre de pixels horizontalement (en anglais width)
  write(fd, &env->res.y, 4); //La hauteur de l'image (sur 4 octets), c'est-à-dire le nombre de pixels verticalement (en anglais height)
  tmp = 1;
  write(fd, &tmp, 2); //Le nombre de plans (sur 2 octets). Cette valeur vaut toujours 1
  write(fd, &env->img.bits_per_pixel, 2); //La profondeur de codage de la couleur(sur 2 octets), c'est-à-dire le nombre de bits utilisés 
  		    		           //pour coder la couleur. Cette valeur peut-être égale à 1, 4, 8, 16, 24 ou 32
  tmp = 0;
  write(fd, &tmp, 4); //La méthode de compression (sur 4 octets). Cette valeur vaut 0 lorsque l'image n'est pas compressée
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
  write(fd, &tmp, 4);
}

void	save_bmp(t_env *env)
{
	int fd;
	int x;
	int y;

	fd = open("salope.bmp", O_CREAT | O_WRONLY)
}
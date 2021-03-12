/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:16:21 by vserra            #+#    #+#             */
/*   Updated: 2021/03/12 17:09:50 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_ctrl(t_env *env)
{
	// printf("SPLENDIDE !\n");
	double zbuffer [env->res.x];

	// tableaux utilisés pour trier les sprites
	int spriteOrder[env->nbsprite];
	double spriteDistance[env->nbsprite];

	// SPRITE CASTING
	// trier les sprites de loin à pret
	int i = 0;
	while (i < env->nbsprite)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((env->ply.px - env->sprite[i].x) * (env->ply.px - env->sprite[i].x) + (env->ply.py - env->sprite[i].y) * (env->ply.py - env->sprite[i].y)) ; // sqrt pas pris, inutile

		i++;
	}
}

// // 1D Zbuffer
// double ZBuffer [env->res.x];

// // tableaux utilisés pour trier les sprites
// int spriteOrder [numSprites];
// double spriteDistance [numSprites];

// // fonction utilisée pour trier les sprites
// void sortSprites (int * order, double * dist, int amount);

// SPRITE CASTING
	 // trier les sprites de loin à fermer
	 for (int i = 0; i <numSprites; i ++)
	{
	  spriteOrder [i] = i;
	  spriteDistance [i] = ((posX - sprite [i] .x) * (posX - sprite [i] .x) + (posY - sprite [i] .y) * (posY - sprite [i] .y)) ; // sqrt pas pris, inutile
	 }
	sortSprites (spriteOrder, spriteDistance, numSprites);

	// après avoir trié les sprites, faites la projection et dessinez-les
	 pour (int i = 0; i <numSprites; i ++)
	{
	  // traduit la position du sprite en relative à la caméra
	   double spriteX = sprite [spriteOrder [i]]. x - posX;
	  double spriteY = sprite [spriteOrder [i]]. y - posY;

	  // transformer le sprite avec la matrice de caméra inverse
	   // [planeX dirX] -1 [dirY -dirX]
	   // [] = 1 / (planeX * dirY-dirX * planeY) * []
	   // [planeY dirY] [-planeY planeX]
 
	  double invDet = 1.0 / (planeX * dirY - dirX * planeY); // requis pour une multiplication correcte de la matrice

	  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
	  double transformY = invDet * (-planeY * spriteX + planeX * spriteY); // c'est en fait la profondeur à l'intérieur de l'écran, ce que Z est en 3D

	  int spriteScreenX = int ((w / 2) * (1 + transformX / transformY));

	  // calculer la hauteur du sprite à l'écran
	   int spriteHeight = abs (int (h / (transformY))); // utiliser 'transformY' au lieu de la distance réelle empêche fisheye
	   // calculer le pixel le plus bas et le plus élevé pour remplir la bande courante
	   int drawStartY = -spriteHeight / 2 + h / 2;
	  if (drawStartY <0) drawStartY = 0;
	  int drawEndY = spriteHeight / 2 + h / 2;
	  if (drawEndY> = h) drawEndY = h - 1;

	  // calcul de la largeur du sprite
	   int spriteWidth = abs (int (h / (transformY)));
	  int drawStartX = -spriteWidth / 2 + spriteScreenX;
	  if (drawStartX <0) drawStartX = 0;
	  int drawEndX = spriteWidth / 2 + spriteScreenX;
	  if (drawEndX> = w) drawEndX = w - 1;

	  // boucle à travers chaque bande verticale du sprite à l'écran
	   pour (int stripe = drawStartX; stripe <drawEndX; stripe ++)
	  {
		int texX = int (256 * (bande - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		// les conditions dans le if sont:
		 // 1) c'est devant le plan de la caméra donc vous ne voyez pas les choses derrière vous
		 // 2) c'est sur l'écran (à gauche)
		 // 3) c'est sur l'écran (à droite)
		 // 4) ZBuffer, avec une distance perpendiculaire
		 if (transformY> 0 && stripe> 0 && stripe <w && transformY <ZBuffer [stripe])
		for (int y = drawStartY; y <drawEndY; y ++) // pour chaque pixel de la bande courante
		 {
		  int d = (y) * 256 - h * 128 + spriteHeight * 128; // 256 et 128 facteurs pour éviter les flottants
		   int texY = ((d * texHeight) / spriteHeight) / 256;
		  Uint32 couleur = texture [sprite [spriteOrder [i]]. Texture] [texWidth * texY + texX]; // récupère la couleur actuelle de la texture
		   if ((color & 0x00FFFFFF)! = 0) buffer [y] [stripe] = color; // peindre le pixel s'il n'est pas noir, le noir est la couleur invisible
		 }
	  }
	}
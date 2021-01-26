/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:05:43 by vserra            #+#    #+#             */
/*   Updated: 2021/01/26 15:51:03 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	game_update(t_env *env)
{
	// if (env->keyboard[KEY_ESCAPE])
	// 	ft_quit(env);
	// if(env->keyboard[KEY_D] && env->square_origin.x < env->parse.resx)
	// 	env->square_origin.x++;
	// if(env->keyboard[KEY_A] && env->square_origin.x > 0)
	// 	env->square_origin.x--;
	// if(env->keyboard[KEY_W] && env->square_origin.y > 0)
	// 	env->square_origin.y--;
	// if(env->keyboard[KEY_S] && env->square_origin.y < env->parse.resy)
	// 	env->square_origin.y++;
	int x; // chaque bande verticale de la fenetre, permet de parcourir les rayons

	x = 0;
	while (x < env->parse.resx)
	{
		// calculer la position et la direction
		env->cameraX = 2 * x / (double)env->parse.resx - 1; // coordonnée x dans l'espace caméra
		env->rayDirX = env->dirX + env->planeX * env->cameraX;
		env->rayDirY = env->dirY + env->planeY * env->cameraX;
		// dans quel carré de la carte nous nous trouvons
		env->mapX = (int)env->posX;
		env->mapY = (int)env->posY;
		// longueur du rayon d'un côté x ou y au coté x ou y
		env->deltaDistX = sqrt(1 + (env->rayDirY * env->rayDirY) / (env->rayDirX * env->rayDirX)); // = deltaDistX = abs (1 / rayDirX);
		env->deltaDistY = sqrt(1 + (env->rayDirX * env->rayDirX) / (env->rayDirY * env->rayDirY)); // = deltaDistY = abs (1 / rayDirY);
		env->hit = 0; // y a-t-il eu un mur touché?

		// calculer le pas et le sideDist initial
		if(env->rayDirX < 0)
		{
			env->stepX = -1;
			env->sideDistX = (env->posX - env->mapX) * env->deltaDistX;
		}
		else
		{
			env->stepX = 1;
			env->sideDistX = (env->mapX + 1.0 - env->posX) * env->deltaDistX;
		}
		if(env->rayDirY < 0)
		{
			env->stepY = -1;
			env->sideDistY = (env->posY - env->mapY) * env->deltaDistY;
		}
		else
		{
			env->stepY = 1;
			env->sideDistY = (env->mapY + 1.0 - env->posY) * env->deltaDistY;
		}
		// exécute DDA
		while (env->hit == 0)
		{
			// passe au carré suivant de la carte, OU dans la direction x, OU dans la direction y
			if(env->sideDistX < env->sideDistY)
			{
				env->sideDistX += env->deltaDistX;
				env->mapX += env->stepX;
				env->side = 0; // c'est un cote x qui est touche (vertical)
			}
			else
			{
				env->sideDistY += env->deltaDistY;
				env->mapY += env->stepY;
				env->side = 1; // c'est un cote y qui est touche (horizontal)
			}
			// Vérifie si le rayon a heurté un mur
			if(env->parse.map[env->mapX][env->mapY] > 0) // == '1' ?
				env->hit = 1;
		}
		// Calculer la distance projetée sur la direction de la caméra (la distance euclidienne donnera un effet fisheye!)
		if(env->side == 0)
			env->perpWallDist = (env->mapX - env->posX + (1 - env->stepX) / 2) / env->rayDirX;
		else
			env->perpWallDist = (env->mapY - env->posY + (1 - env->stepY) / 2) / env->rayDirY;




		// Calcule la hauteur de la colonne à dessiner sur l'écran
		env->lineHeight = (int)(h / env->perpWallDist); // h = hauteur fenetre ?

      // calcule le pixel le plus bas et le plus élevé pour remplir la bande courante
      int drawStart = -env->lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = env->lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

      // choisissez la couleur du mur
      ColorRGB color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;    break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      // donne aux côtés x et y une luminosité différente
      if(side == 1) {color = color / 2;}

      // dessine les pixels de la bande comme une ligne verticale
      verLine(x, drawStart, drawEnd, color);
    }
    // timing pour l'entrée et le compteur FPS
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; // frameTime est le temps que cette image a pris, en secondes
    print(1.0 / frameTime); // Compteur FPS
    redraw();
    cls();

    // modificateurs de vitesse
    double moveSpeed = frameTime * 5.0; // la valeur constante est en carrés / seconde
    double rotSpeed = frameTime * 3.0; // la valeur constante est en radians / seconde
    readKeys();
    // avance si pas de mur devant toi
    if(keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    // recule si aucun mur derrière vous
    if(keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    // tourner vers la droite
    if(keyDown(SDLK_RIGHT))
    {
      // La direction de la caméra et le plan de la caméra doivent être tournés
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    // tourner vers la gauche
    if(keyDown(SDLK_LEFT))
    {
      // La direction de la caméra et le plan de la caméra doivent être tournés
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  }
		x++;
	}

	ft_bzero(env->img.data, env->img.size_line * env->parse.resy);
	mlx_put_image_to_window(env->mlx, env->window, env->img.image, 0, 0);
	return (0);
}

int	start_mlx(t_env *env)
{
	env->posX = 22;  // position de départ du joueur x
	env->posY = 12; // position de départ du joueur y
	env->dirX = -1; // vecteur de direction initiale (commence à -1 pour N, 1 pour S, 0 sinon)
	env->dirY = 0; // vecteur de direction initiale (commence à -1 pour W, 1 pour E, 0 sinon)
	env->planeX = 0;
	env->planeY = 0.66; // la version 2D raycaster du plan de la caméra

	env->time = 0; // heure de la trame courante
	env->oldTime = 0; // heure de l'image précédente
	// env->parse.resx = 1200;
	// env->parse.resy = 600;

	if ((env->mlx = mlx_init()) == NULL)
		mlx_error(&env->parse, MLX_INIT);
	screen_size(env);
	if (!(env->window = mlx_new_window(env->mlx, env->parse.resx, env->parse.resy, "Mon super titre")))
		mlx_error(&env->parse, NEW_WINDOW);
	if (!(env->img.image = mlx_new_image(env->mlx, env->parse.resx, env->parse.resy)))
		mlx_error(&env->parse, NEW_IMAGE);
	env->img.data = (int*)mlx_get_data_addr(env->img.image, &env->img.bits_per_pixel, &env->img.size_line, &env->img.endian);
	ft_putstr_fd("Le temps est bon, le ciel est bleu !\n", 1);
	mlx_hook(env->window, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, env);
	mlx_hook(env->window, KEYPRESS, KEYPRESSMASK, ft_key_press, env);
	mlx_hook(env->window, KEYRELEASE, KEYRELEASEMASK, ft_key_release, env);
	mlx_loop_hook(env->mlx, game_update, env);
	mlx_loop(env->mlx);
	return (0);
}
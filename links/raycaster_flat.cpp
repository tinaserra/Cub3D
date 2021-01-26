/*
Copyright (c) 2004-2019, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(int /*argc*/, char */*argv*/[])
{
  double posX = 22, posY = 12;  // position de départ du joueur x et y
  double dirX = -1; // vecteur de direction initiale (commence à -1 pour N, 1 pour S, 0 sinon)
  double dirY = 0; // vecteur de direction initiale (commence à -1 pour W, 1 pour E, 0 sinon)
  double planeX = 0, planeY = 0.66; // la version 2D raycaster du plan de la caméra

  double time = 0; // heure de la trame courante
  double oldTime = 0; // heure de l'image précédente

  screen(screenWidth, screenHeight, 0, "Raycaster"); // l'écran est créé avec une résolution de notre choix (screenWidth 640 screenHeight 480)
  while(!done()) // la gameloop démarre, c'est la boucle qui dessine une image entière et lit l'entrée à chaque fois
  {
    for(int x = 0; x < w; x++)
    {
      // calculer la position et la direction
      double cameraX = 2 * x / (double)w - 1; // coordonnée x dans l'espace caméra
      double rayDirX = dirX + planeX * cameraX; // la direction du rayon x
      double rayDirY = dirY + planeY * cameraX; // la direction du rayon y
      // dans quel carré de la carte nous nous trouvons
      int mapX = int(posX);
      int mapY = int(posY);

      // longueur du rayon de la position actuelle au cote x ou y suivant
      double sideDistX;
      double sideDistY;

       // longueur du rayon d'un côté x ou y au coté x ou y suivant
      double deltaDistX = std::abs(1 / rayDirX); // = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      double deltaDistY = std::abs(1 / rayDirY); // = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      double perpWallDist; // distance du joueur au mur

      // dans quelle direction avancer dans la direction x ou y (+1 ou -1)
      int stepX;
      int stepY;

      int hit = 0; //1 si un mur a ete touche, 0 sinon
      int side; // Un mur NS ou EW a-t-il été touché?
      // calculer le pas et le sideDist initial
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      // exécute DDA
      while (hit == 0)
      {
        // passe au carré suivant de la carte, OU dans la direction x, OU dans la direction y
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        // Vérifie si le rayon a heurté un mur
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }
      // Calculer la distance projetée sur la direction de la caméra (la distance euclidienne donnera un effet fisheye!)
      if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      // Calcule la hauteur de la colonne à dessiner sur l'écran
      int lineHeight = (int)(h / perpWallDist); // h = hauteur fenetre ?

      // calcule le pixel le plus bas et le plus élevé pour remplir la bande courante
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
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
}

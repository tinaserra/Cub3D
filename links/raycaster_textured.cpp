/*
** Copyright (c) 2004-2019, Lode Vandevenne
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


#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

Uint32 buffer[screenHeight][screenWidth];

int main(int /*argc*/, char */*argv*/[])
{
  double posX = 22.0, posY = 11.5;  //x and y start position
  double dirx = -1.0, diry = 0.0; //initial direction vector
  double planex = 0.0, planey = 0.66; //the 2d raycaster version of camera plane

  double time = 0; //time of current frame
  double oldtime = 0; //time of previous frame

  std::vector<Uint32> texture[8];
  for(int i = 0; i < 8; i++) texture[i].resize(texWidth * texHeight);

  screen(screenWidth,screenHeight, 0, "Raycaster");

  //generate some textures
// #if 0
  // for(int x = 0; x < texWidth; x++)
  // for(int y = 0; y < texHeight; y++)
  // {
  //   int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
  //   //int xcolor = x * 256 / texWidth;
  //   int ycolor = y * 256 / texHeight;
  //   int xycolor = y * 128 / texHeight + x * 128 / texWidth;
  //   texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
  //   texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
  //   texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
  //   texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
  //   texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
  //   texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
  //   texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
  //   texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
  // }
// #else
 //generate some textures
  unsigned long tw, th;
  loadImage(texture[0], tw, th, "pics/eagle.png");
  loadImage(texture[1], tw, th, "pics/redbrick.png");
  loadImage(texture[2], tw, th, "pics/purplestone.png");
  loadImage(texture[3], tw, th, "pics/greystone.png");
  loadImage(texture[4], tw, th, "pics/bluestone.png");
  loadImage(texture[5], tw, th, "pics/mossy.png");
  loadImage(texture[6], tw, th, "pics/wood.png");
  loadImage(texture[7], tw, th, "pics/colorstone.png");
// #endif

  //start the main loop
  while(!done())
  {
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double camerax = 2 * x / (double)w - 1; //x-coordinate in camera space
      double raydirx = dirx + planex*camerax;
      double raydiry = diry + planey*camerax;

      //which box of the map we're in
      int map.x = int(posX);
      int map.y = int(posY);

      //length of ray from current position to next x or y-side
      double sidedistx;
      double sidedisty;

      //length of ray from one x or y-side to next x or y-side
      double deltadistx = std::abs(1 / raydirx);
      double deltadisty = std::abs(1 / raydiry);
      double pwalldist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepx;
      int stepy;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(raydirx < 0)
      {
        stepx = -1;
        sidedistx = (posX - map.x) * deltadistx;
      }
      else
      {
        stepx = 1;
        sidedistx = (map.x + 1.0 - posX) * deltadistx;
      }
      if(raydiry < 0)
      {
        stepy = -1;
        sidedisty = (posY - map.y) * deltadisty;
      }
      else
      {
        stepy = 1;
        sidedisty = (map.y + 1.0 - posY) * deltadisty;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sidedistx < sidedisty)
        {
          sidedistx += deltadistx;
          map.x += stepx;
          side = 0;
        }
        else
        {
          sidedisty += deltadisty;
          map.y += stepy;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[map.x][map.y] > 0) hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
      if(side == 0) pwalldist = (map.x - posX + (1 - stepx) / 2) / raydirx;
      else          pwalldist = (map.y - posY + (1 - stepy) / 2) / raydiry;

      //Calculate height of line to draw on screen
      int lineheight = (int)(h / pwalldist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawstart = -lineheight / 2 + h / 2;
      if(drawstart < 0) drawstart = 0;
      int drawend = lineheight / 2 + h / 2;
      if(drawend >= h) drawend = h - 1;

      //texturing calculations
      int texNum = worldMap[map.x][map.y] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = posY + pwalldist * raydiry;
      else          wallX = posX + pwalldist * raydirx;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && raydirx > 0) texX = texWidth - texX - 1;
      if(side == 1 && raydiry < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineheight;
      // Starting texture coordinate
      double texPos = (drawstart - h / 2 + lineheight / 2) * step;
      for(int y = drawstart; y < drawend; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
    }

    drawBuffer(buffer[0]);
    for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
    //timing for input and FPS counter
    oldtime = time;
    time = getTicks();
    double frameTime = (time - oldtime) / 1000.0; //frametime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw();

    //speed modifiers
    double movespeed = frameTime * 5.0; //the constant value is in squares/second
    double rotspeed = frameTime * 3.0; //the constant value is in radians/second

    readKeys();
    //move forward if no wall in front of you
    if(keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirx * movespeed)][int(posY)] == false) posX += dirx * movespeed;
      if(worldMap[int(posX)][int(posY + diry * movespeed)] == false) posY += diry * movespeed;
    }
    //move backwards if no wall behind you
    if(keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirx * movespeed)][int(posY)] == false) posX -= dirx * movespeed;
      if(worldMap[int(posX)][int(posY - diry * movespeed)] == false) posY -= diry * movespeed;
    }
    //rotate to the right
    if(keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double olddirx = dirx;
      dirx = dirx * cos(-rotspeed) - diry * sin(-rotspeed);
      diry = olddirx * sin(-rotspeed) + diry * cos(-rotspeed);
      double oldplanex = planex;
      planex = planex * cos(-rotspeed) - planey * sin(-rotspeed);
      planey = oldplanex * sin(-rotspeed) + planey * cos(-rotspeed);
    }
    //rotate to the left
    if(keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double olddirx = dirx;
      dirx = dirx * cos(rotspeed) - diry * sin(rotspeed);
      diry = olddirx * sin(rotspeed) + diry * cos(rotspeed);
      double oldplanex = planex;
      planex = planex * cos(rotspeed) - planey * sin(rotspeed);
      planey = oldplanex * sin(rotspeed) + planey * cos(rotspeed);
    }
    if(keyDown(SDLK_ESCAPE))
    {
      break;
    }
  }
}

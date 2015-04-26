// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>
#include <SDL_image.h>

#include <stdlib.h>

#include "window.h"

extern window Window;

class graphics
{
  public:  
    graphics();
    ~graphics();

    void DrawBG(SDL_Surface *img, int x, int y);
    SDL_Surface * LoadPicture(char *file);
    void DrawIMG(SDL_Surface *destsurface, SDL_Surface *img, int x, int y);
    void DrawPartOfIMG(SDL_Surface *destsurface, SDL_Surface *img, int x, int y, int w, int h, int x2, int y2);
    void SetTransparentColor(SDL_Surface *image, Uint8 r, Uint8 g, Uint8 b);
};

#endif

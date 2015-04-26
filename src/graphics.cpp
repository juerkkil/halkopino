// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004

#include "graphics.h"

graphics::graphics()
{
}


graphics::~graphics()
{
}

void graphics::DrawBG(SDL_Surface *img, int x, int y) 
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, Window.GetScreen(), &dest);
}

SDL_Surface * graphics::LoadPicture(char *file)
{
  SDL_Surface *picture;
  picture=IMG_Load(file);
  if (picture <= 0) {
    fprintf(stderr, "Couldn't load file \"%s\" .. \n", file);
    exit (1);
  }
  picture = SDL_DisplayFormat(picture);
  if (picture==NULL) {
    printf("Out of memory!\n");
    exit(1);
  }
  fprintf (stderr, "Loaded file \"%s\" .. \n", file);
  return picture;
}

void graphics::DrawIMG(SDL_Surface *destsurface, SDL_Surface *img, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, destsurface, &dest);
}

void graphics::DrawPartOfIMG(SDL_Surface *destsurface, SDL_Surface *img, int x, int y, int w, int h, int x2, int y2)
{
  SDL_Rect dest;
  SDL_Rect dest2;
  dest.x = x;
  dest.y = y;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, destsurface, &dest);
}


void graphics::SetTransparentColor(SDL_Surface *image, Uint8 r, Uint8 g, Uint8 b) 
{
  SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format, r, g, b));
}

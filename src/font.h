// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004-2005

#ifndef FONT_H
#define FONT_H


#include "window.h"
#include "graphics.h"
#include "variable.h"
#include <string>

extern variable Variable;
extern graphics Graphics;

#define FONT_NORMAL 0x000000
#define FONT_XCENTERED 0x000010
#define FONT_YCENTERED 0x000100
#define FONT_CENTERED 0x000110
#define FONT_RIGHTENED 0x001000
#define FONTS 1

#define WHITE_18 0

#define CHARACTERS 187

using std::string;

class font 
{
  public:
  font();
  ~font();

  void ChangeSurface (SDL_Surface *s);

  void Initialize(int fonttype);

  int GetWidth(Uint8 letter);
  int WriteChar(SDL_Surface *screen, Uint8 letter, Uint32 cx, Uint32 cy);
  void WriteString(SDL_Surface *screen, string(stringi), Uint32 cx, Uint32 cy, Uint32 flags);
  private:
  int type;

  SDL_Surface *destsurface;
  SDL_Surface *fontpic;

  Uint32 **fontdata;
  Uint32 spacewidth;
};

#endif

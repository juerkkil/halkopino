// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004-2005
#include <iostream>
#include "font.h"

font::font() {
}

font::~font() {
	delete fontdata;
}

void font::ChangeSurface (SDL_Surface *s) {
  destsurface=s;
}

void font::Initialize(int fonttype) {

  fontdata = new Uint32*[CHARACTERS];
  int i=0;
  for (i=0; i<CHARACTERS; i++) fontdata[i] = new Uint32[2];
  FILE *fontdatafile;

  switch (fonttype) {
    case WHITE_18:
    spacewidth=12;
    fontpic = Graphics.LoadPicture("fonts/white18.png");
    Graphics.SetTransparentColor(fontpic, 0, 0, 0);
    fontdatafile = fopen("fonts/white18.dat", "r");
    for (i=0; i<93; i++) {
      Variable.FromFile_Int(fontdatafile, &fontdata[i][0]);
      Variable.FromFile_Int(fontdatafile, &fontdata[i][1]);
    }
    fclose (fontdatafile);
    break;
    default:
      std::cout << " No such font in font::Initialize()!" << std::endl;
      exit(0);
      break;
    }
  type=fonttype;
}

int font::GetWidth(Uint8 letter) {
  int width=0;
  switch (letter) {
    case ' ':
    width = spacewidth;
    break;
    default:
    width = fontdata[letter-'!'][1];
    break;
  }
  return width;
}

int font::WriteChar(SDL_Surface *screen, Uint8 letter, Uint32 cx, Uint32 cy) 
{
  int width=0;
  switch (letter) 
  {
    case ' ':
    width = spacewidth;
    break;
    default:
    Graphics.DrawPartOfIMG(screen, fontpic, cx, cy, 
    fontdata[letter-'!'][1], fontpic->h, fontdata[letter-'!'][0], 0); 
    width=GetWidth(letter);
    break;
  }
  return width;
}

void font::WriteString(SDL_Surface *screen, string(stringi), Uint32 cx, Uint32 cy, Uint32 flags) 
{
  if ( (flags&FONT_XCENTERED)==FONT_XCENTERED) 
  {
    int width=0;
    for (int i=0; stringi[i]!='\0'; i++) width+=GetWidth(stringi[i]);
    cx-=(int)(width/2);
  }
  if ( (flags&FONT_YCENTERED)==FONT_YCENTERED) 
  {
    cy-=(int)(fontpic->h/2);
  }
  if ( (flags&FONT_RIGHTENED)==FONT_RIGHTENED) 
  {
    int width=0;
    for (int i=0; stringi[i]!='\0'; i++) width+=GetWidth(stringi[i]);
    cx -= width;
  }
  for (int i=0; stringi[i]!='\0'; i++) 
  {
    cx+=WriteChar(screen, (Uint8)stringi[i], cx, cy);
  }
}

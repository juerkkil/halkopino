// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"


/**
@author Jussi-Pekka Erkkila
*/
class window
{
public:
  window();
  ~window();

	SDL_Surface * OpenWindow(int width, int height, int bpp, int flags);
	SDL_Surface * GetScreen();
 	
 	void SetTitle(char *text);
 
  private:
  SDL_Surface *screen;
  int oldflags;
    
};

#endif

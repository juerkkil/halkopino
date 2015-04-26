// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004

#include "window.h"

window::window()
{
}


window::~window()
{
}

SDL_Surface * window::OpenWindow(int width, int height, int bpp, int flags) 
{
	if (!flags) 
		flags = oldflags;
	oldflags = flags;
	screen = SDL_SetVideoMode(width, height, bpp, flags);
	return screen;
}

void window::SetTitle(char *text) 
{
	SDL_WM_SetCaption (text, NULL);
}

SDL_Surface * window::GetScreen()
{
  return screen;
}




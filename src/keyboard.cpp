// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004-2005
#include "keyboard.h"

keyboard::keyboard()
{
}


keyboard::~keyboard()
{
}

bool keyboard::Hold(Uint16 key)
{
   SDL_PumpEvents();
   if (keys[key]) return true;
   else return false;
}

void keyboard::HandleInterrupts() 
{
   keys=SDL_GetKeyState(NULL);
   while (SDL_PollEvent(&Event)) 
     {
	if (Event.type == SDL_QUIT)
	  {	
	     SDL_Quit();
	     exit(1);
	  }
	if (keys[SDLK_F10]) 
	  {
	     SDL_Quit();
	     exit(1);
	  }	
     }

}





bool keyboard::Pressed(Uint16 key) 
{
  SDL_PumpEvents();
  if(key == SDLK_NUMLOCK || key == SDLK_CAPSLOCK || key == SDLK_SCROLLOCK) return 0;
  if (keys[key])
  {
    if (keydown[key]==false) 
    {
      keydown[key]=true;
      return 1;
    }

    else keydown[key]++;

    if (keydown[key]>=REPEATDELAY1) 
    {
      keydown[key]-=REPEATDELAY2;
    return 1;
    }
  } 
  else 
  {
    keydown[key]=false;
  }
  return 0;
}


void keyboard::ResetReleased() 
{
  keys=SDL_GetKeyState(NULL);
  for (int i=0; i<SDLK_LAST; i++) 
  {
    keydown[i]=false;
  }
}

void keyboard::ResetDouble() 
{
  for (int i=0; i<SDLK_LAST; i++) 
  {
    keydouble[i]=0;
  }
}

void keyboard::ResetAll() 
{
  keys=SDL_GetKeyState(NULL);
  ResetReleased();
  ResetDouble();
}


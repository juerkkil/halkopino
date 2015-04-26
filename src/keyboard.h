// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004-2005
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL.h"
#include <stdlib.h>

#define REPEATDELAY1 45
#define REPEATDELAY2 7

/**
@author Jussi-Pekka Erkkila
*/
class keyboard
{
 public:
   keyboard();
   ~keyboard();
   
   bool Hold(Uint16 key);
   void HandleInterrupts();
   bool Pressed(Uint16 key);
//   bool KeyPressed();
//   void WaitForKey();
   
   void ResetDouble();
   void ResetReleased();
   void ResetAll(); 
   
 private:
   SDL_Event Event;
   Uint8 *keys;
  
  char keydouble[SDLK_LAST];
  char keydown[SDLK_LAST];
};

#endif

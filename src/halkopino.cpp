// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004-2005, 2008

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <stdlib.h>

#include "SDL.h"

#include "graphics.h"
#include "window.h"
#include "keyboard.h"
#include "game.h"
#include "font.h"
#include "variable.h"
#include "luomu.h"

graphics Graphics;
window Window;
keyboard Keyboard;
game Game;
font Font;
variable Variable;
luomu Luomu;

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  cout <<"Initializing SDL." << endl;
  if(SDL_Init(SDL_INIT_VIDEO)< 0) 
    {
      cout <<"Could not initialize SDL:" << SDL_GetError() << endl;
      SDL_Quit();
    } 
  else
  {
    Window.OpenWindow(553, 574, 32, 0);
    cout << "Videomode initialized correctly." << endl;
  }
  Window.SetTitle("Halkopino 0.6.0");
  
  int a = 1;
  Game.Init();

  
  while(a)
    {	
      a = Game.Start();
    }
  
  SDL_Quit();
  return 0;
}

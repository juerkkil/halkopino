// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004-2005, 2008

#ifndef GAME_H
#define GAME_H

#include "SDL.h"

#include "window.h"
#include "graphics.h"
#include "keyboard.h"
#include "font.h"
#include "variable.h"
#include "luomu.h"

extern window Window;
extern keyboard Keyboard;
extern graphics Graphics;
extern font Font;
extern variable Variable;
extern luomu Luomu;

class game
{
 public:
   game();
   ~game();

   int Start();
   void DrawField();  
   void DrawNextBlock(int blocknum);
   void Init();
   void New();
   
 private:
   int blocknum;
   int rotate;
   int x, y, lines, totallines, allines, scores, level, nextblock;
   bool drop;

   SDL_Surface * bg;
   SDL_Surface * block;

   
};

#endif

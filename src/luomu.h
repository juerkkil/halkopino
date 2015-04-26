// This file is part of Halkopino and Luomu-lib
// (c) Jussi-Pekka Erkkilä 2004-2005

#ifndef LUOMU_H
#define LUOMU_H

#include <fstream>
#include <string>

#include "SDL.h"

#include "window.h"

extern window Window;

using namespace std;

class luomu
{
 public:
   luomu();
   ~luomu();
   
   void loadData(int k);
   void loadChars();
   int charWidth(char a);
   void writeText(int x, int y, string(text), int size);
   void initSurfaces();
   
   int geegee[8][8];
   SDL_Surface *abc[39];
};

#endif

// This file is part of Halkopino and Luomu-lib
// (c) Jussi-Pekka Erkkilä 2004-2005

#include "luomu.h"

luomu::luomu()
{
}

luomu::~luomu()
{
}


void luomu::loadData(int k)
{
   ifstream moolan;
   moolan.open("data/fonts.dat");
   char buffer[64];
   moolan.seekg(65*k);
   moolan.read (buffer,64);
   moolan.close();
   for(int i=0;i<8;i++)
     for(int f=0;f<8;f++)
       geegee[i][f]=(int)buffer[(i*8)+f]-48;
}

void luomu::loadChars()
{   
   int *l, f; 
   for(int u = 0; u < 39; u++)
     {	
	loadData(u);
	l = (int*)abc[u]->pixels;
	f= abc[u]->pitch/4;
	for(int i=0;i<8;i++)
	  for(int h=0;h<8;h++)	  
	    if(geegee[i][h] == 1)
	      l[i*f+h]=0xFFFFFF;
     }
}

int luomu::charWidth(char a)
{
   if(a == 'i') return 6;
   if(a == 'j' || a == 'f' || a == 'p' || a == 'e') return 8;
   if(a == 't' || a == 'l') return 7;
   if(a == ' ') return 6;
   else return 9;
}


void luomu::writeText(int x, int y, string(text), int size)
{
   int *v, *p;  
   for(unsigned int u=0; u < text.length(); u++)
     {
	if( (text[u]-97) >= 0 && (text[u]-97) <= 29 )
	  {	     
	     p = (int*)abc[(text[u]-97)]->pixels;
	     v = (int*)Window.GetScreen()->pixels;
	     for(int o=0;o<8;o++)
	       for(int z=0;z<8;z++)
		 for(int s=0; s < size; s++)
		   for(int ss = 0; ss < size; ss++)
		     v[ (y + s +(o * size) ) * (Window.GetScreen()->pitch/4) + (z * size) + ss + x] =
	       p[o* (abc[(text[u]-97)]->pitch/4) + z];
	  }
	if( (text[u] >= 48) && (text[u] <= 57) )
	  {
	     p = (int*)abc[28+(text[u]-48)]->pixels;
	     v = (int*)Window.GetScreen()->pixels;
	     for(int o = 0; o < 8; o++)
	       for(int z = 0; z<8;z++)
		 for(int s = 0; s < size; s++)
		   for(int ss = 0; ss < size; ss++)
		     v[ (y+s+ (o*size) ) * (Window.GetScreen()->pitch/4) + (z*size) +ss+x] = 
	       p[o*(abc[28+(text[u]-48)]->pitch/4) + z];
	  }
	

		  
   
	x += charWidth((char)text[u]) * size;
     }
   
}

void luomu::initSurfaces()
{
   for(int u = 0; u < 39; u++)
     {
	abc[u] = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
     }
}

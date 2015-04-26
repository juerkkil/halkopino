
// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä, 2004-2005, 2008  
//  
#include "game.h"
#include <string>
#include <iostream>
using std::string;


#include <stdlib.h>
#include <math.h>
#include <time.h>
#define BRICKSIZE 18
#define STARTX 48
#define STARTY 125


char field[13][23];
char blocks[7][4][4][4]= // palikkadata (eli palikat rotatoituna joka suuntaan)
{
     {
	  {{0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}},   
	  {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
	  {{0,1,0,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0}},
	  {{0,0,0,0}, {1,1,1,0}, {0,1,0,0}, {0,0,0,0}}  // T    
     },
     {  
	  {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}, // Z
	  {{0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0}},
	  {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}},
	  {{0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0}}
     },
     {
	  {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}, // S
	  {{0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0}},
	  {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}},
	  {{0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0}}
     },
     {
	  {{0,1,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,0,0}}, // L
	  {{0,0,0,0}, {0,0,1,0}, {1,1,1,0}, {0,0,0,0}},
	  {{1,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,0,0,0}},
	  {{1,1,1,0}, {1,0,0,0}, {0,0,0,0}, {0,0,0,0}}
     },
     {
	  {{1,1,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0}}, // J
	  {{1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0}},
	  {{0,0,1,0}, {0,0,1,0}, {0,1,1,0}, {0,0,0,0}},
	  {{0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0}}
     },
     {
	  {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}}, // I
	  {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
	  {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}},
	  {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}
     },
     {
	  {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, // O
	  {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
	  {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
	  {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}
     }
};

  

game::game()
{
}


game::~game()
{
}

void game::Init()
{
 
   block = Graphics.LoadPicture("data/block.png");
   bg = Graphics.LoadPicture("data/gamebg2.jpg");  
 
   
}


int game::Start()
{
   
	   
   Uint32 update = SDL_GetTicks();
   int a,b;   
   srand(time(0));
   
   
   
   /* muuttujaluetteloa:
     int:
     allines, done, lineblocks, altrotate, blocknum, rotate, x, y, floodbar,  totallines, lines, level, scores
     bool: 
     drop, ifloser
*/
   
   
   int movedelay[15] = {500, 400, 350, 300, 270, 240, 210, 170, 130, 100, 85, 73, 65, 50, 38};
   int done = 0, lineblocks = 0, altrotate = 0;
   
   for(int a =0;a<8;a++)for(int b=0;b<8;b++)Luomu.geegee[a][b]=0;
   Luomu.initSurfaces();
   Luomu.loadChars();
   New();
   rotate = 0;
   
	int floodbar = 0;
   bool ifloser = false;
   char brick[4][4];  
   for(a = 0; a < 4; a++)
     for(b = 0; b < 4; b++) 
       brick[a][b] = 0;
   
   Graphics.DrawBG(bg, 0, 0);
   
   
   
   Luomu.writeText(360, 200, string("scores"), 1);
   Luomu.writeText(360, 220, string("level"), 1);
   Luomu.writeText(360, 240, string("lines"), 1);
   
   Luomu.writeText(360, 120, string("next brick"), 1);
   Luomu.writeText(415, 200, string(Variable.intToString(scores)),1);
   Luomu.writeText(415, 220, string(Variable.intToString(level)),1);
   Luomu.writeText(415, 240, string(Variable.intToString(allines)),1);
   
   
   Luomu.writeText(100, 38, string("halkopino"),1);
   
   DrawNextBlock(nextblock);
   SDL_Flip(Window.GetScreen());
   Keyboard.ResetAll();
   
   while(!done) // Pelin päälooppi
     {
       if(SDL_GetTicks() > update)
	  {	 
	    if(!drop) update += movedelay[level];
	    else update += 15;
	    for(a = 0; a < 4; a++)
	      {
		for(b = 0; b < 4; b++)
		  if(brick[a][b] == 1 && field[x + a][y + 1 + b] != 0) 
		    floodbar++; 
	      }
	    if(!floodbar)
	      {
		Graphics.DrawPartOfIMG(Window.GetScreen(), bg, (STARTX - BRICKSIZE) + x * BRICKSIZE, 
				       STARTY + y * BRICKSIZE, BRICKSIZE * 4, BRICKSIZE * 4, 
				       (STARTX - BRICKSIZE) + x * BRICKSIZE, STARTY + y * BRICKSIZE);   
		y++;
	      }
	    else 
	      {
		if(y < 1) { 	
		  ifloser = true;
		  
		}
		for(a = 0; a < 4; a++)
		  {
		    for(b = 0; b < 4; b++)
		      {
			if(brick[a][b]==1)
			  if(field[x+a][y+b] == 0) field[x + a][y + b] = blocknum + 1;
		      }
		  }
		for(a = 0; a < 4; a++)
		  {
		    for(b = 0; b < 10; b++)
		      {
			if(field[1+b][y+a] != 0 && y+a < 22) lineblocks++;
		      }
		    if(lineblocks == 10) 
		      {
			lines++;
			totallines++;
			allines++;
			for(b = 0; b < 10; b++)
			  {
			    for(int i = 0; i < y+a; i++)
			      {                	
				field[b+1][a+y-i] = field[b+1][a+y-i-1];
				field[b+1][a+y-i-1] = 0;
			      }
			  }
		      }
		    lineblocks = 0;
		  }
		if(lines == 1) scores += 40 * level;
		if(lines == 2) scores += 100 * level;
		if(lines == 3) scores += 250 * level;
		if(lines == 4) scores += 500 * level;
		if(lines != 0) 
		  {
		    Luomu.writeText(415, 200, string(Variable.intToString(scores)),1);
		    Luomu.writeText(415, 220, string(Variable.intToString(level)),1);
		    Luomu.writeText(415, 240, string(Variable.intToString(allines)), 1);
		  }
		lines = 0;
		if(totallines >= 14 && level < 10)
		  {
		    level++; 
		    totallines -= 14;
		  }          
		DrawField();
		drop = false;		 
		y = 0; x = 4;
		blocknum = nextblock;
		nextblock = rand() % 7;
		DrawNextBlock(nextblock);		  
		Luomu.writeText(415, 220, string(Variable.intToString(level)),1);
		
		SDL_UpdateRect(Window.GetScreen(), 380 , 125, 100, 250);
		
	      }
	    floodbar =0;            
	  }   
       
       if(ifloser==true)
	 {
	Luomu.writeText(155, 200, "thank you for playing",1);
	Luomu.writeText(155, 230, "new game      n", 1);
	Luomu.writeText(155, 250, "quit          esc",1);
	   SDL_Flip(Window.GetScreen());a=0;
	   while(!a)
	     {
	       Keyboard.HandleInterrupts();
	       
	       if(Keyboard.Pressed(SDLK_n))
		 {
		   New();
		    
		    update = SDL_GetTicks() + 25;
		   a=1;
		 }	
	       if(Keyboard.Pressed(SDLK_ESCAPE)) 
		 {
		   
		   SDL_FreeSurface(bg); 
		   SDL_FreeSurface(block);
		   return 0;		
		 }
	       
	     }
	   ifloser = false;
	 }
       
       Keyboard.HandleInterrupts();
       
       
	if(Keyboard.Pressed(SDLK_n))
	  {
	    New();	    
	  }	
	
	if(Keyboard.Pressed(SDLK_ESCAPE))
	  {
	    SDL_FreeSurface(bg); 
	    SDL_FreeSurface(block);
	    return 0;
	  }
	if(Keyboard.Pressed(SDLK_UP))
	  {	
	    
	    if(rotate == 3) altrotate = 0;
	    else altrotate = rotate+ 1;
	    
	    for(a = 0; a < 4; a++) 
	      for(b = 0; b < 4; b++)
		{
		  brick[a][b] = 0;
		  if(blocks[blocknum][altrotate][a][b] == 1)  brick[a][b] = 1;
		}
	     
	    for(a = 0; a < 4; a++)
	      {
		for(b = 0; b < 4; b++)
		  {
		    
		    if(brick[a][b] == 1 && field[x + a][y + b] != 0) floodbar++;
		    
		  }
	      }        
	    
	     if(!floodbar)
	       {
		 rotate++;
		 if(rotate > 3) rotate = 0;
		 if(rotate < 0) rotate = 3;
		 Graphics.DrawPartOfIMG(Window.GetScreen(), bg, (STARTX - BRICKSIZE) + x * BRICKSIZE, 
					STARTY + y * BRICKSIZE, BRICKSIZE * 4, BRICKSIZE * 4, (STARTX - BRICKSIZE) + x * BRICKSIZE, 
					STARTY + y * BRICKSIZE);
	       }   
	     floodbar = 0;
	  }
	
	if(Keyboard.Pressed(SDLK_DOWN))
	  {
	    update -= (update - SDL_GetTicks());
	    drop = true;
	  }
	
	
	if(Keyboard.Pressed(SDLK_p))
	  {	
	    SDL_Delay(300); Keyboard.ResetReleased();
	    
	    while(!Keyboard.Pressed(SDLK_p));
	    
	    update=SDL_GetTicks() + movedelay[level];
	  }
	
	if(Keyboard.Pressed(SDLK_RIGHT))
	  {
	     for(a = 0; a < 4; a++)
	       {
		 for(b = 0; b < 4; b++)
		   {
		     if(brick[a][b] == 1 && field[x + 1 + a][y + b] != 0) floodbar++;
		   }
	       }
	     if(!floodbar)
	       {
		 Graphics.DrawPartOfIMG(Window.GetScreen(), bg, (STARTX - BRICKSIZE) + (x-1) * BRICKSIZE, 
					STARTY + y * BRICKSIZE, BRICKSIZE * 4, BRICKSIZE * 4,(STARTX - BRICKSIZE) + (x-1) 
					* BRICKSIZE, STARTY + y  * BRICKSIZE);    
		 x++; 
	       }
	     floodbar = 0;
	  }
	
	if(Keyboard.Pressed(SDLK_LEFT))
	  {
	    for(a = 0; a < 4; a++)
	      {
		for(b = 0; b < 4; b++)
		  {
		    if(brick[a][b] == 1 && field[x - 1 + a][y + b] != 0) floodbar++;
		  }
	      }
	    
	     if(!floodbar)
	       {
		 Graphics.DrawPartOfIMG(Window.GetScreen(), bg, (STARTX - BRICKSIZE) + x * BRICKSIZE, 
					STARTY + y * BRICKSIZE, BRICKSIZE * 4, BRICKSIZE * 4,(STARTX - BRICKSIZE) + x 
					* BRICKSIZE, STARTY + y  * BRICKSIZE);
		 x--;		  
	       }
	     floodbar = 0;
	  }	
	for(a = 0; a < 4; a++)
	  {
	    for(b = 0; b < 4; b++)
	       {
		 brick[a][b] = 0;
		 if(blocks[blocknum][rotate][a][b] == 1)
		   {
		     brick[a][b] = 1;	       
		     Graphics.DrawPartOfIMG(Window.GetScreen(), block, (STARTX - BRICKSIZE) + (a + x) * BRICKSIZE, 
					    STARTY + (b + y) * BRICKSIZE, BRICKSIZE, BRICKSIZE, 0, 0 + (blocknum * BRICKSIZE));   
		   }
	       }
	  } 
	for(a = 1; a < 11; a++)
	  {
	    for(b = 0; b < 22; b++) {
	      if(field[a][b] != 0)  
		Graphics.DrawPartOfIMG(Window.GetScreen(), block, (STARTX - BRICKSIZE) + a * BRICKSIZE, 
				       STARTY + b  * BRICKSIZE, BRICKSIZE, BRICKSIZE, 0, 0 +  ((field[a][b] - 1) * BRICKSIZE));   
	    }
	  }		
	SDL_UpdateRect(Window.GetScreen(), 47, 100, 200, 440);
	SDL_Delay(5);
     }
   
   
   
   return 0;
}

void game::DrawField()
{
  for(int blaaba = 1; blaaba < 11; blaaba++)
    {
      for(int blaada = 0; blaada < 22; blaada++)
	{
	  if(field[blaaba][blaada] != 0) 
	    Graphics.DrawPartOfIMG(Window.GetScreen(), block, (STARTX - BRICKSIZE) + blaaba * BRICKSIZE, 
				   STARTY + blaada  * BRICKSIZE, BRICKSIZE, BRICKSIZE, 0, 0 +  ((field[blaaba][blaada] - 1) * BRICKSIZE));   
	  else
	    Graphics.DrawPartOfIMG(Window.GetScreen(), bg, (STARTX - BRICKSIZE) + blaaba * BRICKSIZE, 
				   STARTY + blaada * BRICKSIZE, BRICKSIZE, BRICKSIZE, (STARTX - BRICKSIZE) + blaaba * BRICKSIZE, 
				   STARTY + blaada * BRICKSIZE);  
	}
    }
}

void game::DrawNextBlock(int blocknum)
{
  
  int foo = 0; foo = blocknum;
  
  for(int b = 0; b < 3; b++)
    for(int a = 0; a < 4; a++)
      {
	
	if(blocks[foo][0][a][b] == 1)
	  Graphics.DrawPartOfIMG(Window.GetScreen(), block, 380 + (a* BRICKSIZE), 130 + (b * BRICKSIZE), 
				 BRICKSIZE,  BRICKSIZE, 0, 0 + (blocknum*18));
	else
	  Graphics.DrawPartOfIMG(Window.GetScreen(), bg, 380 + (a * BRICKSIZE), 130 + (b* BRICKSIZE),
				 BRICKSIZE, BRICKSIZE, 380 + (a*BRICKSIZE), 130 + (b*BRICKSIZE));
      }
  
  
}

void game::New()
{
   for(int a=0; a < 12; a++) /* Nollataan tetriskenttä */
     {
       for(int b=0; b < 23; b++)
	 {
	   if(a == 0 || a == 11 || b == 23) field[a][b] = 1;
	   else field[a][b]=0;
	 }
       
     }  
   
   
   
   for(int a = 0; a < 22; a++) /* Rajataan tetriskenttä */ 
     {
       field[11][a] = 1;
       field[0][a] = 1;
       if(a < 11) field[a][22] = 1;
     }
   
   DrawField();
   drop = false;		
   lines = 0; totallines = 0; scores = 0; level = 1; allines =0; 
   y = 0; x = 4;
   blocknum = rand() % 7;
   nextblock = rand() % 7;
   Graphics.DrawPartOfIMG(Window.GetScreen(), bg, 415, 200, 40, 50, 415, 200);

   DrawNextBlock(nextblock);
   Luomu.writeText(415, 200, string(Variable.intToString(scores)),1);
   Luomu.writeText(415, 220, string(Variable.intToString(level)),1);
   Luomu.writeText(415, 240, string(Variable.intToString(allines)),1);
   SDL_UpdateRect(Window.GetScreen(), 365 , 125, 100, 300);
}


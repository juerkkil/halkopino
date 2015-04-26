CXX=g++
DEBUGFLAGS= -Wall
CXXFLAGS=-fprofile-arcs `sdl-config --cflags` $(DEBUGFLAGS)
LIBS= `sdl-config --libs` -lSDL_image -lSDL_ttf 
OBJ=src/halkopino.o src/graphics.o src/window.o src/keyboard.o src/game.o src/font.o src/variable.o src/luomu.o

P_NAME=halkopino

all: halkopino

halkopino: $(OBJ)
		$(CXX) $(OBJ) -o $(P_NAME) $(CXXFLAGS) $(LIBS) -O2 -g

clean:
	rm src/*.o
	rm $(P_NAME)
	rm src/*.gc*	

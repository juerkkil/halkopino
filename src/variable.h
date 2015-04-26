// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <stdlib.h>
#include <string.h>


#include "SDL.h"
#include <string>
using std::string;

class variable 
{
  public:
  void FromFile_Int(FILE *stream, Uint32 *data);
  string intToString(int num);
};




#endif

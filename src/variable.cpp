// This file is part of Halkopino
// (c) Jussi-Pekka Erkkilä 2004


#include "variable.h"


void variable::FromFile_Int(FILE *stream, Uint32 *data) {
  unsigned char byte[4];
  for (int i=0; i<4; i++) byte[i] = fgetc (stream);
  *data = (byte[0]<<24) | (byte[1]<<16) | (byte[2]<<8) | (byte[3]);

}

string variable::intToString(int num)
{
   const int ASCII_INT_OFFSET = 48; 
   const int NUMBER_BASE = 10;
   string sNumber; 
   bool negative = false; 
   if (num < 0)
     {
	negative = true;
	num *= -1; 
     }
   sNumber = char((num % NUMBER_BASE) + ASCII_INT_OFFSET);
   while (num >= NUMBER_BASE)
     {
	num = (num - (num % NUMBER_BASE)) / NUMBER_BASE;
	sNumber = char((num % NUMBER_BASE) + ASCII_INT_OFFSET) + sNumber;
     }
   if (negative)
     {
	sNumber = "-" + sNumber;
     }
   return sNumber;
}



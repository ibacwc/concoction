#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <math.h>

char* WrapText(char* text, int size, int lineSize);
int Collided(int x1, int y1, int w1, int h1,\
			 int x2, int y2, int w2, int h2);

#endif

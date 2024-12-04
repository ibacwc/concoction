#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Window_s{
	SDL_Window* win;
	SDL_Renderer* rend;
	char* title;
}Window;

Window* create_window(char* title, int width, int height);


#endif

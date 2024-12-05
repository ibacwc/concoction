#include "utils.h"

const double PI = 3.1415926535;

int init(){
	if(SDL_Init(SDL_INIT_EVERYTHING)){
		printf("Could not init everything\n");
		return 0;
	}
	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
		printf("Could not init img\n");
		return 0;
	}
	TTF_Init();
	if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK | MIX_INIT_OGG)){
		printf("Could not init mix\n");
		return 0;
	}


}

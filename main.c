#include <stdio.h>
#include <raylib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int main (int argc, char ** argv){
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "game");
	SetTargetFPS(60);
	
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("IAYM", 400, 300, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

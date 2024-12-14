#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <raylib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

Font terminus;

int SHOULD_RUN = 0;
int Init(){
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "game");
	SetTargetFPS(60);
	SetExitKey(KEY_DELETE);
	terminus = LoadFontEx("data/terminus.ttf", 500, 0, 250);
	return 2;
}

void Input(){
	if(WindowShouldClose()) SHOULD_RUN=1;
	if(SHOULD_RUN == 1){
		if(IsKeyPressed(KEY_Y)) SHOULD_RUN=0;
		else if (IsKeyPressed(KEY_N)) SHOULD_RUN=2;
	}
}
void Update(){
}
void Render(){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	if(SHOULD_RUN == 1){
		DrawRectangle(0,200,800,200,BLACK);
		DrawText("Exit? [y/N]", 280, 250, 32, WHITE);
	}

	EndDrawing();
}

int main (int argc, char ** argv){
	SHOULD_RUN = Init();
	while(SHOULD_RUN){
		Input();
		Update();
		Render();
	}
	CloseWindow();
	return 0;
}

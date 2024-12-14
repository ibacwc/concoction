#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <raylib.h>
#include <raymath.h>
#include "inc/utils.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define GAME_WIDTH 320
#define GAME_HEIGHT 240

Font terminus;

int SHOULD_RUN = 0;
RenderTexture2D target;
float scale = 0.0;
Vector2 mouse;
Vector2 virtualMouse;

int Init(){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "game");
	SetWindowMinSize(GAME_WIDTH, GAME_HEIGHT);
	SetTargetFPS(60);
	SetExitKey(KEY_DELETE);

	terminus = LoadFontEx("data/terminus.ttf", 500, 0, 250);

	target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
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
	scale = min((float)GetScreenWidth()/GAME_WIDTH, (float)GetScreenHeight()/GAME_HEIGHT);
	mouse=GetMousePosition();
	virtualMouse.x=(mouse.x - (GetScreenWidth() - (GAME_WIDTH*scale))*0.5f)/scale;
	virtualMouse.y=(mouse.y - (GetScreenHeight() - (GAME_HEIGHT*scale))*0.5f)/scale;
	virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0,0}, (Vector2){(float)GAME_WIDTH, (float)GAME_HEIGHT});

}
void Render(){
	BeginTextureMode(target);

	if(SHOULD_RUN == 1){
		DrawRectangle(0,10,GAME_WIDTH,GAME_HEIGHT/10,BLACK);
		DrawText("Testing", 10, 20,20,GREEN);
	}

	EndTextureMode();
	BeginDrawing();
	DrawTexturePro(target.texture, (Rectangle){0.0f,0.0f,(float)target.texture.width,(float)-target.texture.height},\
		(Rectangle){(GetScreenWidth()-((float)GAME_WIDTH*scale))*.5f,(GetScreenHeight() - ((float)GAME_HEIGHT*scale))*.5f,\
		(float)GAME_WIDTH*scale, GAME_HEIGHT*scale}, (Vector2){0,0},0.0f, WHITE);
	ClearBackground(RAYWHITE);
	EndDrawing();
}

int main (int argc, char ** argv){
	SHOULD_RUN = Init();
	while(SHOULD_RUN){
		Input();
		Update();
		Render();
	}
	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}

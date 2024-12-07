#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>


#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define PAGE_WIDTH 300
#define PAGE_HEIGHT 413
#define H_PW PAGE_WIDTH/2
#define H_PH PAGE_HEIGHT/2


enum PAGE_TYPE { MILITARY,
	FOREIGN,
	INTEL,
	SCI,
	NUCLEAR,
	VULN,
	WMD,
	TAX,
	COMPLAINT,
	SUGGESTION,
	RANDOM
};

typedef struct Page_s{
	char* text;
	enum PAGE_TYPE type;
	int position[2];
	int following;
}Page;
Page ActivePage;
Page tmp = {"bla bla blablah", TAX, {10, 50}, -1};

int SHOULD_RUN = 0;

int Collided(int x1, int y1, int w1, int h1,\
			 int x2, int y2, int w2, int h2){
	if (x1+w1 >= x2 &&\
		x1 <= x2+w2 &&\
		y1+h1 >= y2 &&\
		y1 <= y2+h2) return 1;
	return 0;
}

int Init(){
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "game");
	SetTargetFPS(60);
	SetExitKey(KEY_DELETE);
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
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		if(Collided(GetMouseX(), GetMouseY(), 1, 1,\
			tmp.position[0], tmp.position[1], PAGE_WIDTH, PAGE_HEIGHT)){
			tmp.following = -tmp.following;
		}
	}
	if(tmp.following==1){
		tmp.position[0]=GetMouseX()-H_PW;
		tmp.position[1]=GetMouseY()-H_PH;
	}

}
void Render(){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	DrawRectangle(tmp.position[0], tmp.position[1], PAGE_WIDTH, PAGE_HEIGHT, BEIGE);

	
	if(SHOULD_RUN == 1){
		DrawRectangle(0,200,800,200,BLACK);
		DrawText("Exit? [y/N]", 280, 250, 48, WHITE);
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

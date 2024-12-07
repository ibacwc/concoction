#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <raylib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define PAGE_WIDTH 300
#define PAGE_HEIGHT 413
#define PAGE_FONT_SIZE 20
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
	RANDOM,
	INFO,
};

typedef struct Page_s{
	char* text;
	enum PAGE_TYPE type;
	int clickedAt[2];
	int position[2];
	int following;
}Page;

Font terminus;
Page* activePage;
Page currPage;
Page nextPage;
Page tutorialPage;

int SHOULD_RUN = 0;
char* WrapText(char* text, int size, int lineSize){
	int charsInLine = floor((float)lineSize/(size/2));
	int textWidth = strlen(text)*size;
	char* retVal = malloc((strlen(text) +textWidth/size+1)*sizeof(char));
	retVal[0]='\0';
	int lastIndex=0;
	char* tmp = malloc(strlen(text) * sizeof(char));
	tmp[0]='\0';
	for(int i = 0; i<textWidth/size+1;++i){
		if(i == 0) continue;
		if(i%charsInLine == 0 ){
			//smart
			int insPos=i;
			if (i != charsInLine) strcat(retVal, "\n");
			while(text[insPos] != ' ' || insPos-lastIndex > charsInLine){
				--insPos;
			}
			++insPos;
			strncpy(tmp, text+lastIndex, insPos-lastIndex);
			tmp[insPos-lastIndex]='\0';
			strcat(retVal, tmp);
			lastIndex=insPos;

			//basic
//			strncpy(tmp, text+lastIndex, i-lastIndex);
//			tmp[i]='\0';
//			strcat(retVal, tmp);
//			lastIndex=i;
		}
		if(i==textWidth/size){
			int insPos=i;
			if (i != charsInLine) strcat(retVal, "\n");
			while(text[insPos] != ' ' || insPos-lastIndex > charsInLine){
				--insPos;
			}
			++insPos;
			strncpy(tmp, text+lastIndex, insPos-lastIndex);
			tmp[insPos-lastIndex]='\0';
			strcat(retVal, tmp);
			lastIndex=insPos;
		}
		
	}
	if((strlen(text+lastIndex)-lastIndex)>= charsInLine){
		strcat(retVal, "\n");
	}
	strncat(retVal, text+lastIndex, strlen(text)-lastIndex);
	return retVal;
}
int Collided(int x1, int y1, int w1, int h1,\
			 int x2, int y2, int w2, int h2){
	if (x1+w1 >= x2 &&\
		x1 <= x2+w2 &&\
		y1+h1 >= y2 &&\
		y1 <= y2+h2) return 1;
	return 0;
}
void SetCurrentPage(Page* page){
	page->following = -page->following;
	if(page->following == 1)activePage = page;
	else activePage = NULL;
}
int Init(){
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "game");
	SetTargetFPS(60);
	SetExitKey(KEY_DELETE);
	terminus = LoadFontEx("data/terminus.ttf", 500, 0, 250);
	char* tutorialText = "1 page = 0.08MJ. 1 folder = 100 pages = 8MJ. 1MJ = 0.0125$. A house needs 200MJ = 2.5$, you have 500 houses to heat (1250$). You can achieve this by paying (like you're supposed to) OR you can burn some documents to get that extra cash for yourself. Don't burn anything important, though, or you may lose your job and be arrested!";
	char* brokenText = WrapText(tutorialText, PAGE_FONT_SIZE, PAGE_WIDTH);
	tutorialPage = (Page){brokenText, INFO, {0,0},{0,0}, -1};
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
			tutorialPage.position[0], tutorialPage.position[1], PAGE_WIDTH, PAGE_HEIGHT)){
			tutorialPage.clickedAt[0] = GetMouseX()-tutorialPage.position[0];
			tutorialPage.clickedAt[1] = GetMouseY()-tutorialPage.position[1];
			SetCurrentPage(&tutorialPage);
		}
	}
	if(activePage){
		activePage->position[0]=GetMouseX()-activePage->clickedAt[0];
		activePage->position[1]=GetMouseY()-activePage->clickedAt[1];
	}

}
void RenderPage(Page* page){
	DrawRectangle(page->position[0], page->position[1], PAGE_WIDTH, PAGE_HEIGHT, BEIGE);
	DrawTextEx(terminus, page->text, (Vector2){page->position[0]+5,page->position[1]+10},PAGE_FONT_SIZE, 0,BLACK);
}
void Render(){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	RenderPage(&tutorialPage);
	
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

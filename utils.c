#include "inc/utils.h"
char* WrapText(char* text, int size, int lineSize){
	int charsInLine = floor((float)lineSize/ceil(size/2));
	if(lineSize%2) --charsInLine;
	int textWidth = strlen(text)*size;
	char* retVal = malloc((strlen(text) +textWidth/size+1)*sizeof(char));
	retVal[0]='\0';
	int lastIndex=0;
	char* tmp = malloc(strlen(text) * sizeof(char));
	tmp[0]='\0';
	for(int i = 0; i<strlen(text)+1;++i){
		if(i == 0) continue;
		if(i%charsInLine == 0  || i==strlen(text)){
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

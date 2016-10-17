#pragma once
#include <conio.h>
#include "stdafx.h"
#include <string.h>
#include <stdlib.h> 

void FileName(char *path);
int OpenFile();
int CloseFile();
int CleanBuffer();

FILE *pMySpFile;
int Checking;
char *FullPathFile;

void FileName(char *path) {
	FullPathFile = path;
	OpenFile();
}

int OpenFile() {
	//НЕ УДАЛЯТЬ. ЕЩЁ ПОНАДОБИТСЯ.		//КОГДА?
	/*pBuf = &Buf[0];					//КОГДА ЭТО ПОНАДОБИТСЯ?
	if (pBuf == NULL) { exit(1); }*/	//О ЧЁМ Я ВООБЩЕ ТОГДА ДУМАЛ?
	pMySpFile = fopen(FullPathFile, "r");
	if (!pMySpFile) { 
		printf("An error occurred while opening the file. Treat to the help.");
		exit(1);
	}
	return 1;
}

int CloseFile() {
	Checking = fclose(pMySpFile);
	return 1;
}

//Зачем? Зачем захламлять память этой функцией? 
/*Если функция будет когда-либо использоваться - убрать комментарии*/
/*int CleanBuffer() {
	for (int i = 0; i < strlen(Buf); i++) {
		//Buf[i] = '';
	}
	return 1;
}*/
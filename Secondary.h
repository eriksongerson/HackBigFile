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
	//�� �������. �٨ �����������.		//�����?
	/*pBuf = &Buf[0];					//����� ��� �����������?
	if (pBuf == NULL) { exit(1); }*/	//� ר� � ������ ����� �����?
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

//�����? ����� ���������� ������ ���� ��������? 
/*���� ������� ����� �����-���� �������������� - ������ �����������*/
/*int CleanBuffer() {
	for (int i = 0; i < strlen(Buf); i++) {
		//Buf[i] = '';
	}
	return 1;
}*/
//��������! ���� ���� ��� ��������� � ��������� ���� ������� ������� wc. � ���� ��. 
//�������� GNU.
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Secondary.h"

#define COUNT(x) if(x == '\n') lcount++;
	
int getline();

//typedef unsigned long count; // ������� ����� ���. �����?

unsigned long lcount;
unsigned long total_lcount = 0; // ����� �����

int getline() {
	int c;

	if (feof(pMySpFile))
		return 0;

	while ((c = getc(pMySpFile)) != EOF)
	{
		COUNT(c);
	}

	for (; c != EOF; c = getc(pMySpFile))
	{
		COUNT(c);
	}

	return c != EOF;
}

int Counter();

int Counter() {
	lcount = 0;
	while (getline())
		;

	//printf("%6lu\n", lcount);
	total_lcount += lcount;
	return total_lcount;
}
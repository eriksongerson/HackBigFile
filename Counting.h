//ВНИМАНИЕ! Этот файл был переписан с исходного кода команды Линукса wc. У меня всё. 
//Лицензия GNU.
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Secondary.h"

#define COUNT(x) if(x == '\n') lcount++;
	
int getline();

//typedef unsigned long count; // объявил новый тип. Зачем?

unsigned long lcount;
unsigned long total_lcount = 0; // всего линий

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
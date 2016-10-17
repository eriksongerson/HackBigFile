// Hack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Secondary.h"
#include "Counting.h"
#include <string.h>
#include <map>
#include <iostream>
#include <string>

using namespace std;

/*Функции, выводящие сообщение о help'е, и, собстна, help*/
void PrintLaws();
void PrintHelp();

/*Функция, считающая строки (нет).*/
//int Counting(int);

/*Функции, которые считают и выводят (нет) почтовые сервисы*/
int SearchEmails();
void BustEmail();
void InsertEmailMap();
void PrintEmails();

/*Функции, которые считают количество аккаунтов, имеющих второй пароль*/
void FindSecondPass();
int BustSecPass();

char *pArg;
const char f[]{ "-f" };							//1
const char file[]{ "--file" };					//1
const char help[]{ "--help" };					//1
const char q[]{ "-?" };							//1
const char e[]{ "-e" };							//0
const char h[]{ "--hash" };						//0
const char s[]{ "-s" };							//0
const char same[]{ "--same" };					//0
const char o[]{ "-o" };							//0
const char output[]{ "--output" };				//0
const char c[]{ "-c" };							//1.r
const char linecount[]{ "--count" };			//1.r
const char secondPass[]{ "--spass" };			//1
const char sp[]{ "-sp" };						//1

/*Итого: 8 функций. Необходимо некоторые переписать. Для таких функций ставлю в комментарий букву 'r'*/

char *path;
char *pEmail;
char *pBuf;

unsigned long int WorkForCount = 0; //здесь храним количество строк

int WorkForSecPass = 0;

char Buf[10000];

#define WBUF pBuf = &Buf[0];

/*в начале программы надо узнать путь входного файлика*/
bool WorkInput = false; //если true - файл подключен
						/*а если есть выходной - то ещё и выходного*/
bool WorkOutput = false;

map <string, int> MapEmails;
map <string, int>::iterator cur;

int main(int argc, char *argv[])
{
	if (argc < 2) PrintLaws();
	else {
		for (int i = 1; i < argc; i++) {
			pArg = argv[i];

			if (strcmp(pArg, q) == 0 || strcmp(pArg, help) == 0) {
				PrintHelp();
			}

			if ((strcmp(pArg, f) == 0 || strcmp(pArg, file) == 0) && WorkInput == false) {
				path = argv[i + 1];
				FileName(path);
				i++;
				WorkInput = true;
			}
			else if (WorkInput == false) {
				printf("\nYou did not connect the file\n");
				exit(1);
			}
			else if (strcmp(pArg, c) == 0 || strcmp(pArg, linecount) == 0) {
				if (WorkForCount == 0) {
					WorkForCount = Counter();
				}
				printf("%d", WorkForCount);
				WBUF;
			}
			else if (strcmp(pArg, e) == 0) {
				SearchEmails(); 
				PrintEmails();
				WBUF;
			}
			else if (strcmp(pArg, secondPass) == 0 || strcmp(pArg, sp) == 0) { FindSecondPass(); WBUF;}
		}
		CloseFile();
	}
	return 0;
}

void PrintLaws() {
	printf("\nTo display the help on using the program, enter the argument \"--help\" or \"-?\"\n");
	exit(1);
}

void PrintHelp() {
	printf("\nThis program is designed to work with the dump passwords and");
	printf("logins Myspace.com site, which had previously been procured in a text file.\n\n");
	printf("Use:\thackBigFile [options]\n\n");
	printf("-f[path]\t--file[path]\tOpen a file. Required argument.\n");
	printf("-o[path]\t--output[path]\tThe output of information received in the specified file.\n\t\t\t\tPriority argument. It means\n");
	printf("-c\t\t--count\t\tCounting the number of records\n");
	printf("-e\t\t\t\tSearch, counting, displaying the number of the same e - mail services\n");
	printf("-h\t\t--hash\t\tConclusion password hash\n");
	printf("-u\t\t\t\tPassword Decryption\n");
	printf("-s\t\t--same\t\tSearch and counting identical passwords\n");
	printf("-?\t\t--help\t\tDisplay information about using the program\n");
	exit(1);
}

/*Ниже представленная функция рабочая, но я отказался от неё из-за религиозных причин.
Рабочая версия другой считающей функции лежит в Counting.h. Почему? Потому что так сложилось исторически. 
И вообще Windows, мягко говоря - г****. Линукс лучше тем, что там есть командочка wc. 
WC - 2 буквы и никаких проблем.*/

/*int Counting(int A) {
OpenFile();

if (A == 0) {
printf("\nCounting lines ... \n");
}

unsigned long int j = 0;

do
{
Checking = fscanf(pMySpFile, "%s", Buf);
j++;
} while (Checking != EOF);

j--;	//потому что цикл "проходит" лишний круг

WorkForCount = j;

if (A == 0) {
CloseFile();
}
return j;
}*/

int SearchEmails() {
	if (WorkForCount == 0) {
		WorkForCount = Counter(); //Считаем количество строк и используем их в цикле.
	}
	int Del = 0;
	int A = 0;
	for (int i = 0; i < WorkForCount;i++) {
		int Checker = fscanf(pMySpFile, "%s", Buf);
		WBUF;
		for (int j = 0; j < strlen(Buf);j++) {
			int Write = 0;
			if (*pBuf == ':') { Del = 1; }
			if (*(pBuf + 1) == '\'' && *(pBuf + 2) == '\'' && Del == 1) { Del = 0; pBuf++; break; }
			if (*pBuf == '@') {
				pEmail = pBuf;
				BustEmail();
				InsertEmailMap();
				*(pEmail + strlen(pEmail)) = ':';
				goto endCycle;
			}
			pBuf++;
		}
	endCycle:
		pBuf++;
	}
	return 1;
}

void BustEmail() {
	int Del = 0;
	int l = 0;	//Счётчик нужен для возврата строки, содержащей e-mail в изначальное положение.
	for (int i = 0; i < strlen(pEmail); i++) {
		if (*pEmail == ':') {
			*pEmail = '\0';
			break;
		}
		l++;
		pEmail++;
	}
	pEmail -= l;
}

void InsertEmailMap() {
	if (MapEmails.count(pEmail) == 0) {
		MapEmails.insert(pair<char*, int>(pEmail, 1));
	}
	else {
		MapEmails[pEmail]++;
	}
}

void PrintEmails() {
		for (cur = MapEmails.begin();cur != MapEmails.end();cur++)
		{
			cout << (*cur).first << ": " << (*cur).second << endl;
		}
}

void FindSecondPass() {
	if (WorkForCount == 0) {
		WorkForCount = Counter();
	}
	for (int i = 0; i < WorkForCount; i++) {
		fscanf(pMySpFile, "%s", Buf);
		WBUF;
		BustSecPass();
	}
	printf("\nThe number of accounts with a second password - %d\n", WorkForSecPass);
}

int BustSecPass() {
	int l = 0;
	int j = 0;
	for (j; j < strlen(Buf); j++) {
		if (*pBuf == ':') {
			l++;
		}
		if (l >= 4 && *(pBuf + 1) != '\'' && *(pBuf + 2) != '\'') {
			WorkForSecPass++;
			goto end;
		}
		if (l >= 4 && *(pBuf + 1) == '\'' && *(pBuf + 2) == '\'') {
			goto end;
		}
		pBuf++;
	}
end:
	return 0;
}
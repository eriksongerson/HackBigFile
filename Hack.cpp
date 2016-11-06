//Hack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <map>
#include <iostream>
#include <string>

using namespace std;

/*Ôóíêöèè äëÿ òîãî, ÷òîáû çàáðàòü èìÿ ôàéëà, îòêðûòü åãî è çàêðûòü, à òàêæå ïåðåîòêðûòü ôàéë. 
Ïåðåîòêðûâàòü ôàéë íóæíî äëÿ òîãî, ÷òîáû ôóíêöèÿ fscanf ÷èòàëà çàïèñè ñ ïåðâîé ñòðîêè.
Íåìíîãî ðàäèêàëüíî.*/
void FileName();
int OpenFile();
int CloseFile();
void ReOpenFile();

/*Ôóíêöèè, âûâîäÿùèå ñîîáùåíèå î help'å, è, ñîáñòíà, help*/
void PrintLaws();
void PrintHelp();

/*Ôóíêöèÿ, ñ÷èòàþùàÿ ñòðîêè (íåò).*/
int Counting();

/*Ôóíêöèè, êîòîðûå ñ÷èòàþò è âûâîäÿò (íåò) ïî÷òîâûå ñåðâèñû*/
int SearchEmails();
void BustEmail();
void InsertEmailMap();
void PrintEmails();
void PrintCurrentEmail();

/*Ôóíêöèè, êîòîðûå èùóò îäèíàêîâûå ïàðîëè.*/
void SearchSamePasses();
void PrintSamePasses();
int BustSamePasses();
int InsertPassMap();
void PrintCurrentPass();

/*Ôóíêöèè, êîòîðûå ñ÷èòàþò êîëè÷åñòâî àêêàóíòîâ, èìåþùèõ âòîðîé ïàðîëü*/
void FindSecondPass();
int BustSecPass();

char *pArg;
const char f[]{ "-f" };							//1
const char file[]{ "--file" };					//1
const char help[]{ "--help" };					//1
const char q[]{ "-?" };							//1
const char e[]{ "-e" };							//1
const char h[]{ "--hash" };						//0
const char s[]{ "-s" };							//1
const char same[]{ "--same" };					//1
const char o[]{ "-o" };							//0
const char output[]{ "--output" };				//0
const char c[]{ "-c" };							//1
const char linecount[]{ "--count" };			//1
const char secondPass[]{ "--spass" };			//1
const char sp[]{ "-sp" };						//1

/*Èòîãî: 8 ôóíêöèé. Íåîáõîäèìî íåêîòîðûå ïåðåïèñàòü. Äëÿ òàêèõ ôóíêöèé ñòàâëþ â êîììåíòàðèé áóêâó 'r'*/

FILE *pMySpFile;

char *path;
char *pEmail;
char *pBuf;
char *pPass;
char *FullPathFile;

unsigned long int WorkForCount = 0; //çäåñü õðàíèì êîëè÷åñòâî ñòðîê

int WorkForSecPass = 0;

char Buf[10000];

#define WBUF pBuf = &Buf[0];

/*â íà÷àëå ïðîãðàììû íàäî óçíàòü ïóòü âõîäíîãî ôàéëèêà*/
bool WorkInput = false; //åñëè true - ôàéë ïîäêëþ÷åí
						/*à åñëè åñòü âûõîäíîé - òî åù¸ è âûõîäíîãî*/
//bool WorkOutput = false;

map <string, int> MapEmails;
map <string, int> MapPasses;
map <string, int>::iterator cur;
map <string, int>::iterator current;

/*Âòîðè÷íûå ôóíêöèè ñäåëàþ çäåñü. Îíè áóäóò ìåøàòü.*/
void FileName() {
	FullPathFile = path;
	//OpenFile();
}

int OpenFile() {
	pMySpFile = fopen(FullPathFile, "r");
	if (pMySpFile == NULL) {
		printf("An error occurred while opening the file. Treat to the help.");
		exit(1);
	}
	return 0;
}

int CloseFile() {
	int Checking = fclose(pMySpFile);
	return 0;
}

void ReOpenFile() {
	CloseFile();
	OpenFile();
}
/*Êîíåö âòîðè÷íûõ ôóíêöèé*/

int main(int argc, char *argv[])
{
	if (argc < 2) PrintLaws();
	else {
		for (int i = 1; i < argc; i++) {
				#pragma loop(hint_parallel(0))
			pArg = argv[i];
			if (strcmp(pArg, q) == 0 || strcmp(pArg, help) == 0) {
				PrintHelp();
			}

			if ((strcmp(pArg, f) == 0 || strcmp(pArg, file) == 0) && WorkInput == false) {
				path = argv[i + 1];
				FileName();
				i++;
				WorkInput = true;
			}
			else if (WorkInput == false) {
				printf("\nYou did not connect the file\n");
				exit(1);
			}
			else if (strcmp(pArg, c) == 0 || strcmp(pArg, linecount) == 0) {
				if (WorkForCount == 0) {
					WorkForCount = Counting();
				}
				//if (pMySpFile != NULL){ CloseFile(); }
				printf("\nThe number of entries in the file: %d\n", WorkForCount);
				WBUF;
			}
			else if (strcmp(pArg, e) == 0) {
				SearchEmails(); 
				printf("\nE-Mail : Number\n");
				PrintEmails();
				WBUF;
				MapEmails.clear();
				//CloseFile();
			}
			else if (strcmp(pArg, s) == 0 || strcmp(pArg, same) == 0) {
				SearchSamePasses();
				printf("\nPassword: Number\n");
				PrintSamePasses();
				WBUF;
				MapPasses.clear();
				//CloseFile();
			}
			else if (strcmp(pArg, secondPass) == 0 || strcmp(pArg, sp) == 0) { 
				FindSecondPass(); 
				WBUF; 
				//CloseFile(); 
			}
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
//	printf("-o[path]\t--output[path]\tThe output of information received in the specified file.\n\t\t\t\tPriority argument. It means\n");
	printf("-c\t\t--count\t\tCounting the number of records\n");
	printf("-e\t\t\t\tSearch, counting, displaying the number of the same e - mail services\n");
//	printf("-h\t\t--hash\t\tConclusion password hash\n");
//	printf("-u\t\t\t\tPassword Decryption\n");
	printf("-s\t\t--same\t\tSearch and counting identical passwords\n");
	printf("-sp\t\t--spass\t\tSearch and display the number of accounts with a second password");
	printf("-?\t\t--help\t\tDisplay information about using the program\n");
	exit(1);
}

int Counting() {
	if (pMySpFile != NULL) { ReOpenFile(); }
	if (pMySpFile == NULL) { OpenFile(); }
	unsigned long int lineCounter = 0;
	while (fgets(Buf, sizeof(Buf), pMySpFile)) {
			#pragma loop(hint_parallel(0))
		lineCounter++;
		//printf("%s", Buf);
		/*if (lineCounter % 1000000 == 0) {
			printf("%d\n", (int)lineCounter);
		}*/
	}
	return lineCounter;
}

int SearchEmails() {
	if (WorkForCount == 0) {
		WorkForCount = Counting(); //Ñ÷èòàåì êîëè÷åñòâî ñòðîê è èñïîëüçóåì èõ â öèêëå.
	}
	if (pMySpFile != NULL) { ReOpenFile(); }
	if (pMySpFile == NULL) { OpenFile(); }
	int Del = 0;
	int A = 0;
	for (int i = 0; i < WorkForCount;i++) {
			#pragma loop(hint_parallel(0))
		fscanf(pMySpFile, "%s", Buf);
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
	//CloseFile();
	return 1;
}

void BustEmail() {
	int Del = 0;
	int l = 0;	//Ñ÷¸ò÷èê íóæåí äëÿ âîçâðàòà ñòðîêè, ñîäåðæàùåé e-mail â èçíà÷àëüíîå ïîëîæåíèå.
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
	int max = 0;
	string MaxKey;
	int lastmaxkey = 100000000;
	for (int i = 0; i < 25; i++) {
		for (cur = MapEmails.begin();cur != MapEmails.end();cur++)
		{	#pragma loop(hint_parallel(0))
			
			if (lastmaxkey != max && lastmaxkey > max && lastmaxkey > (*cur).second && (*cur).second > max) { 
				max = (*cur).second; MaxKey = (*cur).first; 
			}
		}
		//for (cur = MapEmails.begin();cur != MapEmails.end(); cur++) {
			lastmaxkey = max;
			max = 0;
			current = MapEmails.find(MaxKey);
			MaxKey = "";
			PrintCurrentEmail();
		//}
	}
}

void PrintCurrentEmail() {
	cout << (*current).first << ": \t\t" << (*current).second << endl;
}

void FindSecondPass() {
	if (WorkForCount == 0) {
		WorkForCount = Counting();
	}
	if (pMySpFile != NULL) { ReOpenFile(); }
	if (pMySpFile == NULL) { OpenFile(); }
	for (int i = 0; i < WorkForCount; i++) {
			#pragma loop(hint_parallel(0))
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

void SearchSamePasses() {
	if (WorkForCount == 0) {
		WorkForCount = Counting(); //Ñ÷èòàåì êîëè÷åñòâî ñòðîê è èñïîëüçóåì èõ â öèêëå.
	}
	if (pMySpFile != NULL) { ReOpenFile(); }
	if (pMySpFile == NULL) { OpenFile(); }
	for (int i = 0;i < WorkForCount;i++) {
			#pragma loop(hint_parallel(0))
		WBUF;
		BustSamePasses();
	}
}

void PrintSamePasses() {
	int max = 0;
	string MaxKey;
	int lastmaxkey = 100000000;
	for (int i = 0; i < 25; i++) {
		for (cur = MapPasses.begin(); cur != MapPasses.end(); cur++)
		{
				#pragma loop(hint_parallel(0))
			if (lastmaxkey != max && lastmaxkey > max && lastmaxkey > (*cur).second && (*cur).second > max) {
				max = (*cur).second; MaxKey = (*cur).first; 
			}
		}
			lastmaxkey = max;
			max = 0;
			current = MapPasses.find(MaxKey);
			MaxKey = "";
			PrintCurrentPass();
	}
}

void PrintCurrentPass() {
	cout << (*current).first << " : \t\t" << (*current).second << endl;
}

int BustSamePasses() {
	int k = 0;
	int j = 0;
	fscanf(pMySpFile, "%s", pBuf);
	for (j; j < strlen(Buf); j++) {
		if (*pBuf == ':') {
			k++;
		}
		if (*pBuf == ':' && k == 3) { pBuf++; }
		if (k == 3 && *(pBuf + 1) == '\'' && *(pBuf + 2) == '\'') {
			goto end;
		}
		if (k == 3 && *(pBuf + 1) != '\'' && *(pBuf + 2) != '\'') {
			pPass = pBuf;
			int l = 0;//Ñ÷¸ò÷èê íóæåí äëÿ âîçâðàòà ñòðîêè, ñîäåðæàùåé ïàðîëü â èçíà÷àëüíîå ïîëîæåíèå.
			int t = strlen(pPass);
			for (int i = 0; i < t; i++) {
				if (*pPass == ':') {
					*pPass = '\0';
					break;
				}
				l++;
				pPass++;
			}
			pPass -= l;
			InsertPassMap();
			goto end;
		}		
		pBuf++;
	}
end:
	pPass = pBuf;
	return 0;
}

int InsertPassMap() {
	if (MapPasses.count(pPass) == 0) {
		MapPasses.insert(pair<char*, int>(pPass, 1));
	}
	else {
		MapPasses[pPass]++;
	}
	return 0;
}

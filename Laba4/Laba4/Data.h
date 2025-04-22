#ifndef DATA_H
#define DATA_H

#include "Applicants.h"

struct Table {
	int* column_size;
	int column_count;
	int size;
};

char* ReadLine();
char* GetCheckNameData(char* alarm, char* warning);
char* GetCheckAddrData(char* alarm, char* warning);
char* GetCheckDateData(char* alarm, char* warning);
char* IntToCharArray(int number);
int CharArrayToInt(char* text, int length);
int GetCheckIntData(char* alarm, char* warning);
int GetDaysInMonth(int month, int year);
void DisplayApplicants();
void DisplayTableApplicants();
void TableAutoResize();
void TableInit();
void CreateApplicant();

#endif
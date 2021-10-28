#pragma once
#include<windows.h>
#include<algorithm>
#include<cmath>
#include"resource.h"

//Константы
const int PRECESSION = 100000000;
static char mes[] = "Invalid input";

//Структура для хранения вещественного числа в целочисленном предстовлении
struct FloatNumb
{
	int whole;
	int decPart;
	bool neg;
	FloatNumb(int _intPart = 0, int _decPart = -1, bool _neg = false) : whole(_intPart), decPart(_decPart), neg(_neg)
	{}
};

//Прототипы
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
int doColculations(char* input);
int setText(HWND hEdit, char symb, char* str);
int getText(HWND hEdit, char* str);
void doSignNumb(HWND hEdit, char* str, char sign);
void setSign(HWND hEdit, char symb, char* str, int& idx);
bool checkPoint(char* str, int idx);
bool checkInput(char* str);
void strCopy(char* str, char* mes);

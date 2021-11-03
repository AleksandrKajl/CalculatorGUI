#pragma once
#include<windows.h>
#include<algorithm>
#include<cmath>
#include"resource.h"

//Константы
const unsigned long long PRECESSION = 1000000000;

class Input
{
public:
	HWND hEdit;			//Дескриптор окна редактир.
	char input[256];	//Буфер ввода
	int idx;			//Показывает на конец строки, количество символов и текущую позицию
	
//Методы
//Заносим символ в буфер ввода
	void setBuf(char symb);
//Метод устанавливает унарный знак +/- или sqrt
	void doSignVal(char sign);
//Метод записывает арифм. знак в буфер ввода
	void setSign(char sign);
//Метод проверяет число на установленную точку(запятую) 
	bool checkPoint();
//Метод проверки корректного ввода
	bool checkInput();
};

class Calculator
{
	long double result;
	long double lVal;
	long double rVal;
	int lCount;
	int rCount;
	int idx;

//Метод извлечения данных из массива(lValue и rValue)
	void dataExtraction(char* input);
	void extSQRT(char* input);
//Вычесляет колличество символов числа, до арифмитического знака или после
	int numbCount(char* input, int i, bool direction);
public:
//Основной публичный метод
	int doColculations(char* input);
 };

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
//int doColculations(char* input);


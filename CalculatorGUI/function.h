#pragma once
#include<windows.h>
#include<algorithm>
#include<cmath>
#include"resource.h"

//Константы
const unsigned long long PRECESSION = 1000000000;

//Структура для хранения вещественного числа в целочисленном предстовлении
struct FloatNumb
{
	long long whole;
	long long decPart;
	bool neg;
	FloatNumb(int _intPart = 0, int _decPart = -1, bool _neg = false) : whole(_intPart), decPart(_decPart), neg(_neg)
	{}
	void clean();
};

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
	bool checkPoint(int idx);
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
//Метод извлечения квадратного корня из числа
	void extSQRT(char* input);
//Запись результата подвырожения в массив
	void writeRes(char* input);
//Вычесляет колличество символов числа, до арифмитического знака или после
	int numbCount(char* input, int i, bool direction);
//Переводит символы в вещественное число
	double charToDouble(char* input, int i, int numb);
//Переводит веществинные числа в char
	void DoubleToChar(char* buf);
//Разделяет вещественное число на целую и дробную часть
	void devideDouble(FloatNumb& obj, long double val);
//Метод перевода int в char
	void intToChar(char* buf, FloatNumb& obj);
//Вспомогательный метод который переворачивает массив(Первый символ становится последним)
	void inversArr(char* buf, bool negative, const int SZ);
//Вставляет в массив вместо подвырожения его результат
	void copy(char* input, char* buftmp);

public:
//Основной публичный метод
	int doColculations(char* input);
 };

//Прототипы
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


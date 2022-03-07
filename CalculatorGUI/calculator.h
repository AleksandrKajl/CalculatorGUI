#pragma once
#include<windows.h>
#include<algorithm>
#include<cmath>
#include<string>
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


class Calculator
{
	long double result;
	long double lVal;
	long double rVal;
	int lCount;
	int rCount;
	int idx;

//Метод извлечения данных из массива(lValue и rValue)
	void dataExtraction(std::string& input);
//Метод извлечения квадратного корня из числа
	void extSQRT(std::string& input);
//Запись результата подвырожения в массив
	void writeRes(std::string& input);
//Вычесляет колличество символов числа, до арифмитического знака или после
	int numbCount(std::string& input, int i, bool direction);
//Переводит символы в вещественное число
	double charToDouble(std::string& input, int i, int numb);
//Переводит веществинные числа в char
	void DoubleToChar(std::string& buf);
//Разделяет вещественное число на целую и дробную часть
	void devideDouble(FloatNumb& obj, long double val);
//Метод перевода int в char
	void intToChar(std::string& buf, FloatNumb& obj);
//Вспомогательный метод который переворачивает массив(Первый символ становится последним)
	void inversArr(std::string& buf, bool negative, const int SZ);
//Вставляет в массив вместо подвырожения его результат
	void copy(std::string& input, std::string& buftmp);
	bool checkNull(std::string& buf, int i);

public:
//Основной публичный метод
	int doColculations(std::string& input);
 };

//Прототипы
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


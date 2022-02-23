#pragma once
#include<windows.h>

class Input

{
public:
	HWND hEdit;			//Дескриптор окна редактир.
	char input[256];	//Буфер ввода
	int idx;			//Показывает на конец строки, количество символов и текущую позицию
	int idxSign;

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
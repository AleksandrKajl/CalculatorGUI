#pragma once
#include<windows.h>
#include<string>

class Input

{
public:
	HWND hEdit;			//Дескриптор окна редактир.
	std::string input;	//Буфер ввода
	int idx;			//Показывает на конец строки, количество символов и текущую позицию
	int idxSign;

	Input() : hEdit(0), input(std::string(256,'\0')), idx(0), idxSign() {}
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
#pragma once
#include<windows.h>
#include<string>

class Input

{
public:
	HWND hEdit;			//���������� ���� ��������.
	std::string input;	//����� �����
	int idx;			//���������� �� ����� ������, ���������� �������� � ������� �������
	int idxSign;

	Input() : hEdit(0), input(std::string(256,'\0')), idx(0), idxSign() {}
	//������� ������ � ����� �����
	void setBuf(char symb);
	//����� ������������� ������� ���� +/- ��� sqrt
	void doSignVal(char sign);
	//����� ���������� �����. ���� � ����� �����
	void setSign(char sign);
	//����� ��������� ����� �� ������������� �����(�������) 
	bool checkPoint(int idx);
	//����� �������� ����������� �����
	bool checkInput();
};
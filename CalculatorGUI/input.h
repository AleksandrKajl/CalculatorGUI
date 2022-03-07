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

	Input() : hEdit(0), input(""), idx(0), idxSign() { input.reserve(256); }
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
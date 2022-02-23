#pragma once
#include<windows.h>

class Input

{
public:
	HWND hEdit;			//���������� ���� ��������.
	char input[256];	//����� �����
	int idx;			//���������� �� ����� ������, ���������� �������� � ������� �������
	int idxSign;

	//������
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
#pragma once
#include<algorithm>
//���������
const int PRECESSION = 100000000;



//��������� ��� �������� ������������� ����� � ������������� �������������
struct FloatNumb
{
	int whole;
	int decPart;
	bool neg;
	FloatNumb(int _intPart = 0, int _decPart = -1, bool _neg = false) : whole(_intPart), decPart(_decPart), neg(_neg)
	{}
};

double doColculations(char* input);
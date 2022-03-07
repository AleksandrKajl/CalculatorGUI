#include"input.h"

//������ ������ Input
//#������� ������ �������� � ���� ������������
//#���������: ���������� ���� ����������, �������. ������, ����� ��� ������ ��������
void Input::setBuf(char symb)
{
	//�������� ������� �� ���� ������������ � idx ��������� ��������� �������� ��� \0
	if (idx == 1 && input[0] == '0' && (symb != ',' && symb != '+' && symb != '-' &&
		symb != '*' && symb != '/' && symb != '^' && symb != '%'))
	{
		idx = 0;
	}

	input.push_back(symb);
	input.push_back('\0');
	//���������� ��������� ����, ����� �������
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(input.c_str()));
}

//#������� ������������� ������� ���� +/- ��� sqrt
//#���������: ���������� ���� ����������, ���������� �����, ������� ����
void Input::doSignVal(char sign)
{
	int count{};
	//�������� ������� �� ���� ������������ � idx ��������� ��������� �������� ��� \0
	idx = SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)input.c_str());
	//������������� �� ��������� ������
	int i{ idx - 1 };
	//������� ���������� �������� �� ������� �����. ����� ��� �� �������� ������� ������
	while (input[i] != '-' && input[i] != '+' && input[i] != '*' && input[i] != '/' &&
		input[i] != '^' && input[i] != 'V' && input[i] != '%' && i >= 0)
	{
		++count;
		--i;
	}
	//���� ������ ����� ����������� �����
	if (input[i] == 'V' && sign == '-')
		return;
	else if (input[i] == '-' && sign == 'V')
	{
		SendMessage(hEdit, WM_SETTEXT, 0, LPARAM("Invalid input"));
		return;
	}

	//���� ����� ������� ����
	if (input[i] == sign && (input[i - 1] == '+' || input[i - 1] == '-' ||
		input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '^' ||
		input[i - 1] == '%' || i == 0))
	{
		++count;
	}

	//��������� ���� ��� �����, ���� �� ������
	if (count == 0)
		return;

	//������������� ������ �� ����� ����� ����� �����
	idx -= count;
	char tmpBuf[24]{};
	//�������� ����� ��� �������� ������ ���� �� ��������� �����
	for (int i{}, j{ idx }; i < count; ++i, ++j)
		tmpBuf[i] = input[j];

	//��������� ���� �� ����� �������������
	if (input[idx] == sign && (input[idx - 1] == '+' || input[idx - 1] == '-' ||
		input[idx - 1] == '*' || input[idx - 1] == '/' || input[idx - 1] == '^' ||
		input[idx - 1] == '%' || idx == 0))
	{
		idxSign--;
		//���� ���� �������� ���� ������� ���
		for (int i{ 1 }; i < count; ++i, ++idx)
			input[idx] = tmpBuf[i];
	}
	else
	{
		//���������� ����, ����� �����
		idxSign = idx;				//��������� ������ �����
		input[idx++] = sign;
		for (int i{}; i < count; ++i, ++idx)
			input[idx] = tmpBuf[i];
	}

	input[idx] = '\0';
	//���������� ��������� ����, ����� �������
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(input.c_str()));
}

//#������� ������ �����. ������ � �����
void Input::setSign(char sign)
{
	//�������� �� ��� ����� ������
	if (input[idx - 1] == '+' || input[idx - 1] == '-' || input[idx - 1] == '*' ||
		input[idx - 1] == '/' || input[idx - 1] == ',' || input[idx - 1] == '^' ||
		input[idx - 1] == '%' || idx == 0)
	{
		return;
	}
	else
	{
		if (sign != ',')
			idxSign = idx;
		setBuf(sign);
	}

}

//#������� ��������� ����� �� ������������� �����(�������) 
bool Input::checkPoint(int idx)
{
	while (input[idx - 1] != '-' && input[idx - 1] != '+' && input[idx - 1] != '*' &&
		input[idx - 1] != '/' && input[idx - 1] != '^' && input[idx - 1] != 'V' &&
		input[idx - 1] != '%' && (idx - 1) != 0)
	{
		if (input[idx - 1] == ',')
			return true;
		--idx;
	}
	return false;
}

//����� �������� ����������� �����
bool Input::checkInput()
{
	int i{};
	//�������� �� �����. ���� � ������
	if (input[i] == '+' || input[i] == '*' || input[i] == '/' || input[i] == ',' ||
		input[i] == '^' || input[i] == '%')
	{
		return false;
	}

	//�������� ����� ����� ������
	if (input[0] != '-' && input[0] != 'V')
	{
		if (input[0] == ',')
			return false;
	}
	else
	{
		if (input[1] == ',')
			return false;
	}

	int cnt{};
	while (input[i] != '\0')
	{

		//��������� ����: �����, �����. ���� ��� ���� ���. ����� 
		if ((input[i] >= '0' && input[i] <= '9') || input[i] == '+' || input[i] == '-' ||
			input[i] == '*' || input[i] == '/' || input[i] == ',' || input[i] == '^' ||
			input[i] == '%' || input[i] == 'V')
		{
			// �������� �� ��� ����� ������
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ||
				input[i] == '^' || input[i] == 'V' || input[i] == '%')
			{
				//��������� ����� � ����� ����� � ����� ������
				if (input[i - 1] == ',' || input[i + 1] == ',')
					return false;
				//���������� ���. ����� � ����� ���������� ����� ������� �� �����
				cnt = 0;
				//������ �����. ����
				if (input[i + 1] == '+' || (input[i + 1] == '-' && input[i + 2] == '-') ||
					input[i + 1] == '*' || input[i + 1] == '/' || input[i + 1] == '^' ||
					input[i + 1] == '%' || (input[i + 1] == 'V' && input[i + 2] == 'V'))
				{
					return false;
				}
			}

			if (input[i] == ',')
			{
				if (++cnt > 1)
					return false;
			}

			i++;
		}
		else
			return false;
	}

	//�������� �� �����. ���� � �����
	if (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' ||
		input[i - 1] == '/' || input[i - 1] == '^' || input[i - 1] == '%' ||
		input[i - 1] == 'V')
	{
		return false;
	}

	return true;
}
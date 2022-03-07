#include"input.h"

//Методы класса Input
//#Функция вывода символов в окно калькулятора
//#Параметры: Дескриптор окна управления, устанав. символ, буфер для вывода символов
void Input::setBuf(char symb)
{
	//Получаем символы из окна калькулятора в idx колиество считанных символов без \0
	if (idx == 1 && input[0] == '0' && (symb != ',' && symb != '+' && symb != '-' &&
		symb != '*' && symb != '/' && symb != '^' && symb != '%'))
	{
		idx = 0;
	}

	input.push_back(symb);
	input.push_back('\0');
	//Отправляет сообщение окну, минуя очередь
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(input.c_str()));
}

//#Функция устанавлевает унарный знак +/- или sqrt
//#Параметры: Дескриптор окна управления, символьный буфер, унарный знак
void Input::doSignVal(char sign)
{
	int count{};
	//Получаем символы из окна калькулятора в idx колиество считанных символов без \0
	idx = SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)input.c_str());
	//Устанавлеваем на последний символ
	int i{ idx - 1 };
	//считаем количество символов до первого арефм. знака или до нулевого индекса буфера
	while (input[i] != '-' && input[i] != '+' && input[i] != '*' && input[i] != '/' &&
		input[i] != '^' && input[i] != 'V' && input[i] != '%' && i >= 0)
	{
		++count;
		--i;
	}
	//Если ставим минус квадратному корню
	if (input[i] == 'V' && sign == '-')
		return;
	else if (input[i] == '-' && sign == 'V')
	{
		SendMessage(hEdit, WM_SETTEXT, 0, LPARAM("Invalid input"));
		return;
	}

	//Если стоял унарный знак
	if (input[i] == sign && (input[i - 1] == '+' || input[i - 1] == '-' ||
		input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '^' ||
		input[i - 1] == '%' || i == 0))
	{
		++count;
	}

	//Проверяем если нет числа, знак не меняем
	if (count == 0)
		return;

	//Устанавлеваем индекс на место сразу после знака
	idx -= count;
	char tmpBuf[24]{};
	//Капируем число для которого меняем знак во временный буфер
	for (int i{}, j{ idx }; i < count; ++i, ++j)
		tmpBuf[i] = input[j];

	//Проверяем было ли число отрицательным
	if (input[idx] == sign && (input[idx - 1] == '+' || input[idx - 1] == '-' ||
		input[idx - 1] == '*' || input[idx - 1] == '/' || input[idx - 1] == '^' ||
		input[idx - 1] == '%' || idx == 0))
	{
		idxSign--;
		//Если было затираем знак который был
		for (int i{ 1 }; i < count; ++i, ++idx)
			input[idx] = tmpBuf[i];
	}
	else
	{
		//Записываем знак, затем число
		idxSign = idx;				//Сохраняем индекс знака
		input[idx++] = sign;
		for (int i{}; i < count; ++i, ++idx)
			input[idx] = tmpBuf[i];
	}

	input[idx] = '\0';
	//Отправляет сообщение окну, минуя очередь
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(input.c_str()));
}

//#Функция записи арифм. знаков в буфер
void Input::setSign(char sign)
{
	//Проверка на два знака подряд
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

//#Функция проверяет число на установленную точку(запятую) 
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

//Метод проверки корректного ввода
bool Input::checkInput()
{
	int i{};
	//Проверка на арифм. знак в начале
	if (input[i] == '+' || input[i] == '*' || input[i] == '/' || input[i] == ',' ||
		input[i] == '^' || input[i] == '%')
	{
		return false;
	}

	//Проверка точки перед числом
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

		//Корректно если: число, арифм. знак или знак дес. дроби 
		if ((input[i] >= '0' && input[i] <= '9') || input[i] == '+' || input[i] == '-' ||
			input[i] == '*' || input[i] == '/' || input[i] == ',' || input[i] == '^' ||
			input[i] == '%' || input[i] == 'V')
		{
			// Проверка на два знака подряд
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ||
				input[i] == '^' || input[i] == 'V' || input[i] == '%')
			{
				//Проверяем точку в конце числа и перед числом
				if (input[i - 1] == ',' || input[i + 1] == ',')
					return false;
				//Переменная кол. точек в числе обнуляется когда даходим до знака
				cnt = 0;
				//Второй арифм. знак
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

	//Проверка на арифм. знак в конце
	if (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' ||
		input[i - 1] == '/' || input[i - 1] == '^' || input[i - 1] == '%' ||
		input[i - 1] == 'V')
	{
		return false;
	}

	return true;
}
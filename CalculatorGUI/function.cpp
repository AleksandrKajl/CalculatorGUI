//ООП
#include"function.h"

//Глобальные переменные
int _exp{};							//Показывает сколько нулей перед числом//#Разделяет целую и дробную часть вещественного числ

//#Принимает: структура в которую заносится результат, число которое предстоит разделить
void devideDouble(FloatNumb& obj, double val)
{
	//Если число отрицательное устанавлеваем влаг
	if (val < 0)
	{
		val = -val;
		obj.neg = true;
	}

	double tmpVal{};
	obj.whole = static_cast<int>(val);

	tmpVal = val - static_cast<float>(obj.whole);
	
	if (tmpVal > 0)
	{
		double tmp = 0.1;
		while (tmpVal < tmp)
		{
			++_exp;
			tmp /= 10;
		}
		obj.decPart = static_cast<int>(tmpVal * PRECESSION);

	}

}

void inversArr(char* buf, bool negative, const int SZ)
{
	int i{};
	if (negative == true)
	{
		buf[SZ] = buf[0];
		buf[0] = '-';
		++i;
	}
	for (int j{ SZ - 1 }; i < j; --j, i++)
		std::swap(buf[i], buf[j]);
}

void intToChar(char* buf, FloatNumb & obj)
{
	int i{};
	while (true)
	{
		if (obj.decPart > 0)
		{
			buf[i] = static_cast<char>(obj.decPart % 10 + '0');
			obj.decPart /= 10;
		}
		else if (obj.decPart == 0)
		{
			if (_exp > 0)
			{
				buf[i] = '0';
				--_exp;
			}
			else
			{
				buf[i] = ',';
				--obj.decPart;
			}
		}
		else if (obj.whole > 0)
		{
			buf[i] = static_cast<char>(obj.whole % 10 + '0');
			obj.whole /= 10;
		}
		else
			break;
		++i;
	}

	inversArr(buf, obj.neg, i);

}

void DoubleToChar(char* buf, double result)
{
	FloatNumb obj;
	devideDouble(obj, result);
	intToChar(buf, obj);
}

void copy(char* input, int& i, int& lnumb, char* buftmp)
{

	i -= lnumb;
	if (i > 0 && input[i - 1] == '-' && (input[i - 2] == '+' || input[i - 2] == '-' || input[i - 2] == '*' || input[i - 2] == '/' || (i - 1) == 0))
		i--;

	int j{};
	while (buftmp[j] != '\0')
	{
		input[i] = buftmp[j];
		j++;
		i++;
	}
}


//#Сжатие массива путём записи вычисленных значений#
//#Принимает: Массив с данными, размер массива, текущая поз. в массиве, результат вырожения,
//кол. символов лев. числа от ар. знака, кол. символов правого числа#
void compressionArr(char* input, int& i, double result, int lnumb, int rnumb)
{
	char buf[256]{};
	if (input[i + (rnumb + 1)] == '\0')
	{
		DoubleToChar(buf, result);
		copy(input, i, lnumb, buf);
		input[i] = '\0';
		i--;				//Чтобы указать на последний символ в массиве и не делать проход по нему
	}
	else
	{
		char buftmp[256]{};
		int j{}, k{ i };

		while (input[k + rnumb + 1] != '\0')
		{
			buftmp[j] = input[k + rnumb + 1];
			j++;
			k++;
		}
		buftmp[j] = '\0';
		j = 0;

		DoubleToChar(buf, result);
		copy(input, i, lnumb, buf);
		int tmp{ i };  //Временная переменная для хранения индекса

		while (buftmp[j] != '\0')
		{
			input[i] = buftmp[j];
			j++;
			i++;
		}
		input[i] = '\0';
		i = tmp - 1;
	}

}


//#Переводит символы в числа#
//#Принимает: массив данных, текущий указатель на последний символ пер. числа, кол. символов в переводимом числе# 
double charToDouble(char* input, int i, int numb)
{
	int i_numb{};
	double f_numb{};
	int tmp{ i };

	int isDegree{ 1 };
	while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && i >= 0 && input[i] != ',' && input[i] != '^' && input[i] != 'V')
	{
		i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
		isDegree *= 10;
		i--;
	}

	if (input[i] == ',' && i >= 0)
	{
		isDegree = 1;
		tmp = tmp - i;
		i--;
		f_numb = (double)i_numb;
		for (int j{}; j < tmp; j++)
		{
			isDegree *= 10;
		}
		f_numb /= isDegree;

		isDegree = 1;
		i_numb = 0;
		while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && i >= 0 && input[i] != '^' && input[i] != 'V')
		{
			i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
			isDegree *= 10;
			i--;
		}
		f_numb += static_cast<float> (i_numb);

		//Если число отрицательное делаем отрицательным
		if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i-1] == '^' || i == 0))
			f_numb = -f_numb;

		return f_numb;
	}

	//Если число отрицательное делаем отрицательным
	if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '^' || i == 0))
		i_numb = -i_numb;

	return i_numb;
}

//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int numbCount(char* input, int i, bool direction)
{
	int numb{};

	//Если полученный результат выражения отрицательное число
	if (input[0] == '-' && (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '^' && input[i] != 'V'))
	{
		++i;
	}

	if (direction != true)
	{
		//Считаем количество символов до следующего знака
		while (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i - 1] != '/' && input[i - 1] != '^' && i != 0)
		{
			++numb;
			--i;
		}
	}
	else
	{
		if (input[i + 1] == '-')//Если унарный минус
		{
			++i;				//Начинаем с него
			++numb;				//И берём его в счёт(в левую сторону не надо)
		}

//Если это результат выражения
		if (i == 0 && input[i] != 'V')
		{
			while (input[i] != '\0')
			{
				++numb;
				++i;
			}
		}
//Иначе
		else
		{
			while (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && input[i + 1] != '/' && input[i + 1] != '^' && input[i + 1] != '\0')
			{
				++numb;
				++i;
			}
		}
	}
	return numb;
}

//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
int doColculations(char* input)
{
	double result{};
	double lNumb{}, rNumb{};
	int lCount{}, rCount{};
	int i{};

	if (input[0] == 'V')
	{
		//lCount = 0;		//Нужно для корректной записи в массив функцией copy 
		rCount = numbCount(input, i, true);
		rNumb = charToDouble(input, i + rCount, rCount);

		result = sqrt(rNumb);
		compressionArr(input, i, result, lCount, rCount);
	}

	//processing * and /
	while (input[i] != '\0')
	{
		if ((input[i] == '*' || input[i] == '/' || input[i] == '^') && input[i+1] != 'V')
		{
			switch (input[i])
			{
			case('*'):
				//Считаем количество символов слево и справо от знака
				lCount = numbCount(input, i, false);
				rCount = numbCount(input, i, true);

				lNumb = charToDouble(input, i - 1, lCount);	//i указывает на символ перед знаком
				rNumb = charToDouble(input, i + rCount, rCount);
				result = lNumb * rNumb;
				compressionArr(input, i, result, lCount, rCount);
				break;

			case('/'):
				lCount = numbCount(input, i, false);
				lNumb = charToDouble(input, i - 1, lCount);
				rCount = numbCount(input, i, true);
				rNumb = charToDouble(input, i + rCount, rCount);

				result = lNumb / rNumb;
				compressionArr(input, i, result, lCount, rCount);
				break;

			case('^'):
				lCount = numbCount(input, i, false);
				lNumb = charToDouble(input, i - 1, lCount);
				rCount = numbCount(input, i, true);
				rNumb = charToDouble(input, i + rCount, rCount);

				result = pow(lNumb, rNumb);
				compressionArr(input, i, result, lCount, rCount);
				break;
			}
		}
		else if (input[i + 1] == 'V')
		{
			int tmp = i;
			i++;
			lCount = 0;		//Нужно для корректной записи в массив функцией copy 
			rCount = numbCount(input, i, true);
			rNumb = charToDouble(input, i + rCount, rCount);
		
			result = sqrt(rNumb);
			compressionArr(input, i, result, lCount, rCount);
			i = tmp - 1;
		}

		i++;
	}
	//Pocessing + and -
	if (input[0] == '-')
		i = 1;
	else
		i = 0;

	while (input[i] != '\0')
	{
		if ((input[i] == '+' || input[i] == '-') && input[i + 1] != 'V')
		{
			switch (input[i])
			{
			case('+'):
				lCount = numbCount(input, i, false);
				lNumb = charToDouble(input, i - 1, lCount);
				rCount = numbCount(input, i, true);
				rNumb = charToDouble(input, i + rCount, rCount);

				result = lNumb + rNumb;
				compressionArr(input, i, result, lCount, rCount);
				break;

			case('-'):
				lCount = numbCount(input, i, false);
				lNumb = charToDouble(input, i - 1, lCount);
				rCount = numbCount(input, i, true);
				rNumb = charToDouble(input, i + rCount, rCount);

				result = lNumb - rNumb;
				compressionArr(input, i, result, lCount, rCount);
				break;
			}
		}
		else if (input[i + 1] == 'V')
		{
			int tmp = i;
			i++;
			lCount = 0;		//Нужно для корректной записи в массив функцией copy 
			rCount = numbCount(input, i, true);
			rNumb = charToDouble(input, i + rCount, rCount);

			result = sqrt(rNumb);
			compressionArr(input, i, result, lCount, rCount);
			i = tmp - 1;
		}

		i++;
	}

	i = 0;
	while (input[i] != '\0')
		++i;

	return i;
}

//#Функция вывода символов в окно калькулятора
//#Параметры: Дескриптор окна управления, устанав. символ, буфер для вывода символов
//#Return: Количество введёных символов без \0
int Input::setBuf(char symb, char* str)
{
	int idx;
//Получаем символы из окна калькулятора в idx колиество считанных символов без \0
	idx = this->getBuf(str);
	str[idx] = symb;
	++idx;
	str[idx] = '\0';
//Отправляет сообщение окну, минуя очередь
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
	return idx;
}

//#Функция для получения символов из окна калькулятора
//#Параметры: Дескриптор окна управления, символьный буфер
//#Return: Количество полученных символов
int Input::getBuf(char* str)
{
	int idx{};
//Отправляет сообщение окну, минуя очередь
	idx = SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)str);
	return idx;
}


//#Функция устанавлевает унарный знак +/- или sqrt
//#Параметры: Дескриптор окна управления, символьный буфер, унарный знак
void Input::doSignNumb(char* str, char sign)
{
	int idx{};
	int count{};
//Получаем символы из окна калькулятора в idx колиество считанных символов без \0
	idx = this->getBuf(str);
//Устанавлеваем на последний символ
	int i{ idx - 1 };
//считаем количество символов до первого арефм. знака или до нулевого индекса буфера
	while (str[i] != '-' && str[i] != '+' && str[i] != '*' && str[i] != '/' && str[i] != '^' && str[i] != 'V' && i >= 0)
	{
		++count;
		--i;
	}
//Если ставим минус квадратному корню
	if (str[i] == 'V' && sign == '-')
		return;
	else if (str[i] == '-' && sign == 'V')
	{
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM("Invalid input"));
			return;
	}

//Если стоял унарный знак
	if (str[i] == sign && (str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^' || i == 0))
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
		tmpBuf[i] = str[j];

//Проверяем было ли число отрицательным
	if (str[idx] == sign && (str[idx - 1] == '+' || str[idx - 1] == '-' ||
		str[idx - 1] == '*' || str[idx - 1] == '/' || str[idx - 1] == '^' || idx == 0))
	{
//Если было затираем знак который был
		for (int i{1}; i < count; ++i, ++idx)
			str[idx] = tmpBuf[i];
	}
	else
	{
//Записываем знак, затем число

		str[idx++] = sign;
		for (int i{}; i < count; ++i, ++idx)
			str[idx] = tmpBuf[i];
	}

	str[idx] = '\0';
//Отправляет сообщение окну, минуя очередь
	SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
}

//#Функция записи арифм. знаков в буфер
void Input::setSign(char symb, char* str, int& idx)
{
	if (str[idx - 1] == '+' || str[idx - 1] == '-' || str[idx - 1] == '*' || str[idx - 1] == '/' || str[idx - 1] == ',' || str[idx - 1] == '^' || idx == 0)
		return;
	else
		idx = this->setBuf(symb, str);
}

//#Функция проверяет число на установленную точку(запятую) 
bool checkPoint(char* str, int idx)
{
	while (str[idx - 1] != '-' && str[idx - 1] != '+' && str[idx - 1] != '*' && str[idx - 1] != '/' && str[idx - 1] != '^' && str[idx - 1] != 'V' && (idx - 1) != 0)
	{
		if (str[idx - 1] == ',')
			return true;
		--idx;
	}
	return false;
}

int len(char* str)
{
	int len{};
	while (str[len] != '\0')
		len++;
	return len;
}

bool checkInput(char* str)
{
	int size{};
	size = len(str);
	int i{};
	//Проверка на арифм. знак в начале
	if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == ',' || str[i] == '^')
	{
		return false;
	}

	//Проверка точки перед числом
	if (str[0] != '-' && str[0] != 'V')
	{
		if (str[0] == ',')
			return false;
	}
	else
	{
		if (str[1] == ',')
			return false;
	}

	int cnt{};
	while (str[i] != '\0')
	{

		//Корректно если: число, арифм. знак или знак дес. дроби 
		if ((str[i] >='0' && str[i] <= '9') || str[i] == '+' || str[i] == '-' ||
			str[i] == '*' || str[i] == '/' || str[i] == ',' || str[i] == '^' || str[i] == 'V')
		{
			// Проверка на два знака подряд
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'V')
			{
				//Проверяем точку в конце числа и перед числом
				if (str[i - 1] == ',' || str[i + 1] == ',')
					return false;
				//Переменная кол. точек в числе обнуляется когда даходим до знака
				cnt = 0;
				//Второй арифм. знак
				if (str[i + 1] == '+' || (str[i + 1] == '-' && str[i + 2] == '-') || str[i + 1] == '*' ||
					str[i + 1] == '/' || str[i + 1] == '^' || (str[i + 1] == 'V' && str[i+2] == 'V'))
				{
					return false;
				}
			}

			if (str[i] == ',')
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
	if (str[size - 1] == '+' || str[size - 1] == '-' || str[size - 1] == '*' || str[size - 1] == '/' || str[size - 1] == '^' || str[size - 1] == 'V')
		return false;

	return true;
}
#include"calculator.h"

//Глобальные переменные
int _exp{};							//Показывает сколько нулей перед числом//#Разделяет целую и дробную часть вещественного числ

void FloatNumb::clean()
{
	whole = 0;
	decPart = -1;
	neg = false;
}

//Методы класса Calculator
//#Разделяет вещественное число на целую и дробную часть
//#Принимает: структура в которую заносится результат, число которое предстоит разделить
void Calculator::devideDouble(FloatNumb& obj, long double val)
{
	//Если число отрицательное устанавлеваем флаг
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
		obj.decPart = static_cast<long long>(tmpVal * PRECESSION);
	}
}

void Calculator::inversArr(char* buf, bool negative, const int SZ)
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

bool Calculator::checkNull(char* buf, int i)
{
	while (i >= 0)
	{
		if (buf[i] != '0')
			return false;
		i--;
	}
	return true;
}

void Calculator::intToChar(char* buf, FloatNumb & obj)
{
	int i{};
	bool check{true};
	while (true)
	{
		if (obj.decPart > 0)
		{
			buf[i] = static_cast<char>(obj.decPart % 10 + '0');
			obj.decPart /= 10;
			if (buf[0] == '0')
				continue;
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
		else if (obj.whole >= 0)
		{
			buf[i] = static_cast<char>(obj.whole % 10 + '0');
			obj.whole /= 10;
			if(obj.whole == 0)
				obj.whole--;
		}
		else
			break;
		++i;
	}

	inversArr(buf, obj.neg, i);

}

void Calculator::DoubleToChar(char* buf)
{
	FloatNumb obj;
	devideDouble(obj, result);
	intToChar(buf, obj);
}

void Calculator::copy(char* input, char* buftmp)
{

	idx -= lCount;
	if (idx > 0 && input[idx - 1] == '-' && (input[idx - 2] == '+' || input[idx - 2] == '-' || 
		input[idx - 2] == '*' || input[idx - 2] == '/' || input[idx - 2] == '^' || 
		input[idx - 2] == '%' || (idx - 1) == 0))
		idx--;

	int j{};
	while (buftmp[j] != '\0')
	{
		input[idx] = buftmp[j];
		j++;
		idx++;
	}
}

//#Запись результата подвырожения в массив
//#Принимает: Массив с данными, размер массива, текущая поз. в массиве, результат вырожения,
//кол. символов лев. числа от ар. знака, кол. символов правого числа#
void Calculator::writeRes(char* input)
{
	char buf[256]{};
	if (input[idx + (rCount + 1)] == '\0')
	{
		DoubleToChar(buf);
		copy(input, buf);
		input[idx] = '\0';
		idx--;				//Чтобы указать на последний символ в массиве и не делать проход по нему
	}
	else
	{
		char buftmp[256]{};
		int j{}, k{ idx };

		while (input[k + rCount + 1] != '\0')
		{
			buftmp[j] = input[k + rCount + 1];
			j++;
			k++;
		}
		buftmp[j] = '\0';
		j = 0;

		DoubleToChar(buf);
		copy(input, buf);
		int tmp{ idx };  //Временная переменная для хранения индекса

		while (buftmp[j] != '\0')
		{
			input[idx] = buftmp[j];
			j++;
			idx++;
		}
		input[idx] = '\0';
		idx = tmp - 1;
	}
}

//#Переводит символы в числа#
//#Принимает: массив данных, текущий указатель на последний символ пер. числа, кол. символов в переводимом числе# 
double Calculator::charToDouble(char* input, int i, int numb)
{
	int i_numb{};
	double f_numb{};
	int tmp{ i };

	int isDegree{ 1 };
	while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' &&
		i >= 0 && input[i] != ',' && input[i] != '^' && input[i] != 'V' && input[i] != '%')
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
		while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && 
			i >= 0 && input[i] != '^' && input[i] != 'V' && input[i] != '%')
		{
			i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
			isDegree *= 10;
			i--;
		}
		f_numb += static_cast<float> (i_numb);

		//Если число отрицательное делаем отрицательным
		if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' ||
			input[i - 1] == '/' || input[i-1] == '^' || input[i - 1] == '%' || i == 0))
			f_numb = -f_numb;

		return f_numb;
	}

	//Если число отрицательное делаем отрицательным
	if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' ||
		input[i - 1] == '/' || input[i - 1] == '^' || input[i - 1] == '%' || i == 0))
		i_numb = -i_numb;

	return i_numb;
}

//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int Calculator::numbCount(char* input, int i, bool direction)
{
	int cnt{};

	//Если полученный результат выражения отрицательное число
	if (input[0] == '-' && (input[i] != '+' && input[i] != '-' && input[i] != '*' && 
		input[i] != '/' && input[i] != '^' && input[i] != '%' && input[i] != 'V'))
	{
		++i;
	}

	if (direction != true)
	{
		//Считаем количество символов до следующего знака
		while (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && 
			input[i - 1] != '/' && input[i - 1] != '^' && input[i - 1] != '%' && i != 0)
		{
			++cnt;
			--i;
		}
	}
	else
	{
		if (input[i + 1] == '-')//Если унарный минус
		{
			++i;				//Начинаем с него
			++cnt;				//И берём его в счёт(в левую сторону не надо)
		}

//Если это результат выражения
		if (i == 0 && input[i] != 'V')
		{
			while (input[i] != '\0')
			{
				++cnt;
				++i;
			}
		}
//Иначе
		else
		{
			while (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && 
				input[i + 1] != '/' && input[i + 1] != '^' && input[i + 1] != '%' && 
				input[i + 1] != '\0')
			{
				++cnt;
				++i;
			}
		}
	}
	return cnt;
}

//#Метод извлечения данных из массива(lValue и rValue)#
//#Принимает массив данных#
void Calculator::dataExtraction(char* input)
{
	//Считаем количество символов слево и справо от знака
	lCount = numbCount(input, idx, false);
	lVal = charToDouble(input, idx - 1, lCount);	//idx указывает на символ перед знаком
	rCount = numbCount(input, idx, true);
	rVal = charToDouble(input, idx + rCount, rCount); //idx показывает на последний символ числа
}

//#Метод извлечения квадратного корня из числа#
//#Принимает массив данных#
void Calculator::extSQRT(char* input)
{
	lCount = 0;		//Нужно для корректной записи в массив функцией copy 
	rCount = numbCount(input, idx, true);
	rVal = charToDouble(input, idx + rCount, rCount);

	result = sqrt(rVal);
	writeRes(input);
}
//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
int Calculator::doColculations(char* input)
{
	if (input[0] == 'V')
		extSQRT(input);

	while (input[idx] != '\0')
	{
		if (input[idx] == '^')
		{
			dataExtraction(input);
			result = pow(lVal, rVal);
			writeRes(input);
		}
		else if (input[idx] == 'V')
		{
			extSQRT(input);
		}
			

		idx++;
	}

	idx = 0;
	//processing * and /
	while (input[idx] != '\0')
	{
		if (input[idx] == '*' || input[idx] == '/' || input[idx] == '%')
		{
			switch (input[idx])
			{
			case('*'):
				dataExtraction(input);
				result = lVal * rVal;
				writeRes(input);
				break;

			case('/'):
				dataExtraction(input);
				result = lVal / rVal;
				writeRes(input);
				break;

			case('%'):
				long long whole {};
				long long decPart{};
				dataExtraction(input);
				FloatNumb obj;
				devideDouble(obj, lVal);
				whole = obj.whole;
				if (obj.decPart != -1)
					decPart = obj.decPart;

				obj.clean();
				devideDouble(obj, rVal);
				whole %= obj.whole;
				if (obj.decPart != -1)
					decPart %= obj.decPart;
				result = static_cast<long double>(decPart) / PRECESSION + whole;
				if (obj.neg == true)
					result = -result;

				writeRes(input);
				break;
			}
		}

		idx++;
	}
	//Pocessing + and -
	if (input[0] == '-')
		idx = 1;
	else
		idx = 0;

	while (input[idx] != '\0')
	{
		if (input[idx] == '+' || input[idx] == '-')
		{
			switch (input[idx])
			{
			case('+'):
				dataExtraction(input);
				result = lVal + rVal;
				writeRes(input);
				break;

			case('-'):
				dataExtraction(input);
				result = lVal - rVal;
				writeRes(input);
				break;
			}
		}

		idx++;
	}

	idx = 0;
	while (input[idx] != '\0')
		++idx;
	idx = 0;

	return idx;
}






















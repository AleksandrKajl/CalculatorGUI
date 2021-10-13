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
	double tmp = 0.1;
	if (tmpVal > 0)
	{
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
	if (input[i - 1] == '-' && (input[i - 2] == '+' || input[i - 2] == '-' || input[i - 2] == '*' || input[i - 2] == '/' || input[i - 2] == '!'))
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
	int count{};
	char buf[256]{};
	if (input[i + (rnumb + 1)] == '!')
	{
		DoubleToChar(buf, result);
		copy(input, i, lnumb, buf);
		input[i] = '!';
		input[i + 1] = '\0';
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
	while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '!' && input[i] != ',')
	{
		i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
		isDegree *= 10;
		i--;
	}

	if (input[i] == ',')
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
		while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '!')
		{
			i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
			isDegree *= 10;
			i--;
		}
		f_numb += static_cast<float> (i_numb);

		//Если число отрицательное делаем отрицательным
		if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '!'))
			f_numb = f_numb - f_numb * 2;

		return f_numb;
	}

	//Если число отрицательное делаем отрицательным
	if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '!'))
		i_numb = i_numb - i_numb * 2;

	return i_numb;
}

//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int numbCount(char* input, int i, bool direction)
{
	int numb{};

	//Если результат выражения отрицательное число
	if (input[1] == '-' && (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/'))
	{
		i++;
	}

	if (direction != true)
	{
		//Считаем количество символов до следующего знака
		while (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i - 1] != '/' && input[i - 1] != '!')
		{
			numb++;
			i--;
		}
	}
	else
	{
		if (input[i + 1] == '-')//Если унарный минус
		{
			i++;				//Начинаем с него
			numb++;				//И берём его в счёт(в левую сторону не надо)
		}

		while (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && input[i + 1] != '/' && input[i + 1] != '!')
		{
			numb++;
			i++;
		}
	}
	return numb;
}


//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
double doColculations(char* input)
{
	double result{};
	double lNumb{}, rNumb{};
	int lCount{}, rCount{};
	int i{ 1 };

	//processing * and /
	while (input[i] != '!')
	{
		if (input[i] == '*')
		{
			//Считаем количество символов слево и справо от знака
			lCount = numbCount(input, i, false);
			rCount = numbCount(input, i, true);

			lNumb = charToDouble(input, i - 1, lCount);	//i указывает на символ перед знаком
			rNumb = charToDouble(input, i + rCount, rCount);
			result = lNumb * rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}
		else if (input[i] == '/')
		{
			lCount = numbCount(input, i, false);
			lNumb = charToDouble(input, i - 1, lCount);
			rCount = numbCount(input, i, true);
			rNumb = charToDouble(input, i + rCount, rCount);

			result = lNumb / rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}

		i++;
	}
	//Pocessing + and -
	i = 1;
	while (input[i] != '!')
	{
		if (input[i] == '-' && input[i - 1] == '!')
		{
			i++;
			continue;
		}

		if (input[i] == '+')
		{
			lCount = numbCount(input, i, false);
			lNumb = charToDouble(input, i - 1, lCount);
			rCount = numbCount(input, i, true);
			rNumb = charToDouble(input, i + rCount, rCount);

			result = lNumb + rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}
		else if (input[i] == '-')
		{
			lCount = numbCount(input, i, false);
			lNumb = charToDouble(input, i - 1, lCount);
			rCount = numbCount(input, i, true);
			rNumb = charToDouble(input, i + rCount, rCount);

			result = lNumb - rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}

		i++;
	}

	i = 0;
	int numb{};
	numb = numbCount(input, 0, true);
	if (input[1] == '-')
		i = 1;

	result = charToDouble(input, numb + i, numb);
	return result;
}

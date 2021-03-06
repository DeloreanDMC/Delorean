/*Милованов Константин 9 группа МОиАИС		
		Найти максимальный среди элементов тех столбцов, которые упорядочены либо по
	возрастанию, либо по убыванию.Если упорядоченные столбцы в матрице отсутствуют, то
	вывести 0.
*/
#include "pch.h"
#include <iostream>
#include <fstream>	
constexpr auto Size = 3;//размер матрицы;

//ввод матрицы c клавиатуры
void InputMatr(int matr[Size][Size]) 
{	
	std::cout << "Введите квадратную матрицу размера:" << Size << "\n";
	//матрица - массив столбцов
	for (int j = 0; j < Size; j++)
		for (int i = 0; i < Size; i++)
			std::cin >> matr[i][j];
}

//ввод матрицы из файла, возразает true если считать данные удалось
bool InputMatrFromFile(std::ifstream &fin, int matr[Size][Size])
{
	if (!fin.is_open()) 
	{
		std::cout << "Не удалось открыть файл!\n";
		return false;
	}
	else 
	{
		char ch;
		//матрица - массив столбцов
		for (int j = 0; j < Size; j++)
		{
			for (int i = 0; i < Size; i++)
				fin >> matr[i][j];
		}
		fin.close(); //закрываем файл
		return true;
	}

}
//Функция проверяет, упорядочен ли столбец матрицы
//Возвращает -1, если упорядочен по убыванию
//Возвращает 1, если упорядочен по возрастанию
//Возвращает 0, если не упорядочен 
int IsOrdered(int matr[Size])
{
	int i = 0;	//счетчик
	int res = matr[0] <= matr[1]; //инициализируем результат (true = 1, false = 0)
	if (res == 1) //если первые два элемента упорядочены по возрастанию
	{
		//пока не дошли до конца и эленты упорядочены по возрастанию
		while ( (i < Size-1 )&& (res==1)) 
		{
			if (matr[i] > matr[i + 1])	//если какие-то два элемнты не упорядочены по возрастанию
				return 0;	//вернуть 0 (элементы вообще не упорядочены)
			else
				i++;	//иначе проверять следующую пару
		}
	}
	else //иначе
	{	//аналогично
		res = -1;
		while ((i < Size - 1) && (res==-1)) {
			if (matr[i] < matr[i + 1])
				return 0;
			else
				i++;
		}
	}
	return res;
}

//функция возвращает максимальный элемент упорядоченного столбца
int Max(int matr[Size],int order) 
{
	int res;	//результат функции
	//мы знаем как массив упорядочен, поэтому
	//если упорядочен по возрастанию - вернуть последний элемент
	//если упорядочен по убыванию - первый
	(order == 1) ? (res = matr[Size - 1]) : (res = matr[0]);	
	return res;
}

//функция реализующая поставленную задачу
int MaxOfAll(int matr[Size][Size]) 
{
	int max;	//значение функции
	int order; //упорядочееность
	bool was_one = false; //переменная следит - был ли хотябы один столбец упорядочен
	for (int i=0; i < Size; i++) 
	{
		order = IsOrdered(matr[i]);	//вычисление упорядоченности
		if (order != 0) //если упорядочен хоть как-то
			if (! was_one) { //если это первый упорядоченный столбец
				max = Max(matr[i],order);	//за мах берем мах первого упорядоченного столбца
				was_one = true;	//поднимаем флажок 
			}
			else
				if (Max(matr[i],order) > max) //если максимальный элемент столбца больше текущего максимума 
					max = Max(matr[i],order);	//переприсваиваем максимум
	}
	if (was_one)	//если хотябы один столбец упорядочен
		return max;	//вернуть максимум
	else
		return 0;	//если ни один столбец не упорядочен, вернуть 0
}

//Функция, отправляющая пользователю запросы на подтверждение выполнения операции
bool InputQuery(const char *txt) 
{
	char ans;
	std::cout << txt << "(Y/N) \n"; //вывод запроса
	std::cin >> ans;	//ввод ответа
	//проверка корректности ответа
	while ((ans != 'y') && (ans != 'Y') && (ans != 'n') && (ans != 'N')) 
	{
		std::cout << "Ошибка! Повторите ввод\n";
		std::cin >> ans;
	}

	return ('Y' == ans) || ('y' == ans);
}

//функция ввода и проверки натурального числа
int InputNumber(const char *txt,int min,int max)
{
	std::cout << txt; 
	int res;
	std::cin >> res;
	while ((min > res) || (max < res))
	{
		std::cout << "Ошибка! Число должно лежать в диапазоне от " << min << " до " << max << "\n";
		std::cout << "Повторите ввод\n";
		std::cin >> res;
	}
	return res;
}

//функция реализующая меню
void SelectMenuItem(int &Item)
{
	std::cout << "1 - Ввод-вывод с клавиатуры\n";
	std::cout << "2 - Ввод-вывод из файла\n";
	std::cout << "0 - Выход\n";
	Item = InputNumber("Выберите пункт меню:\n",0,2);
}

//главная функция программы
int main()
{
	setlocale(LC_ALL, "rus");	//корректное отображение Кириллицы
	//вывод информации о програме
	std::cout << "Програма находит максимальный среди элементов тех столбцов,\nкоторые упорядочены либо по возрастанию, либо по убыванию.\nЕсли упорядоченные столбцы в матрице отсутствуют, то вывести 0\n";
	int matr[Size][Size]; //объявление двумерного целочисленных массива (матрица)
	int Item = -1;//пункт меню
	while (0 != Item) 
	{
		SelectMenuItem(Item);	//меню
		switch (Item)
		{
			case 1: InputMatr(matr);	//ввод данных вручную
			   std::cout << MaxOfAll(matr); //результат
			   if (! InputQuery("Хотите продолжить работу с программой?"))
				   Item = 0;
			   break;
			case 2:  std::ifstream fin("input.txt");  
				if (InputMatrFromFile(fin, matr))
				{
					std::ofstream fout("output.txt");
					fout << MaxOfAll(matr);
					fout.close();
					std::cout << "Процесс успешно завершен, результат в файле - output.txt\n";
				}
				if (!InputQuery("Хотите продолжить работу с программой?"))
					Item = 0;
				break;
		}
	}
	
	
	
	
	
}


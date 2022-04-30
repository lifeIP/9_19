#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
struct coz
{
	char name[64];
	char polusharia[32];
	double koordinati;
	int kolichestvo;

};
void print_menu();
coz* load(const char* file, int& count);
void print(coz* m, int count);
void filter_polusharia(coz* m, int count);
float high_quality(coz* f, int count);
int all_stars(coz* f, int count);





int main()
{
	setlocale(LC_ALL, "RUS");
	int count = 0;
	coz* m = NULL;
	while (1)
	{
		print_menu();
		char ch = _getch();
		switch (ch)
		{
		case '1':
			if (m == NULL)
			{
				m = load("cars.txt", count);
				if (count == -1)
					return 0;
			}
			break;
		case '2':
			if (m != NULL)
				print(m, count);
			break;
		case '3':
			if (m != NULL)
				filter_polusharia(m, count);
			break;
		case '4':
			if (m != NULL)
				cout << high_quality(m, count);
			break;
		case '5':
			if (m != NULL)
				cout << all_stars(m, count);
			break;
		case '0':
			if (m != NULL)
				delete[] m;
			return 0;
			break;
		default:
			cout << "Введена неизвестная команда!" << endl;
		}
	}


	if (m != NULL)
		delete[] m;
}
coz* load(const char* file, int& count)
{
	fstream f;
	f.open(file);
	if (!f.is_open())
	{
		cout << "Не удалось открыть файл " << file << endl;
		count = -1;
		return NULL;
	}
	char buff[100];
	f.getline(buff, 99);
	count = atoi(buff);
	coz* polusharias = new coz[count];
	for (int i = 0; i < count; i++)
	{
		f.getline(polusharias[i].name, 63);
		f.getline(polusharias[i].polusharia, 31);
		f.getline(buff, 99);
		polusharias[i].koordinati = atof(buff);
		f.getline(buff, 99);
		polusharias[i].kolichestvo = atoi(buff);
		if (f.eof())
		{
			cout << "Количество данных недостаточное" << endl;
			count = -1;
			delete[] polusharias;
			f.close();
			return NULL;
		}

	}
	f.close();
	return polusharias;
}
void print(coz* m, int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << endl;
		cout << "название: " << m[i].name << endl;
		cout << " в каких полушариях: " << m[i].polusharia << endl;
		cout << "координаты на небе: " << m[i].koordinati << endl;
		cout << "количество звезд: " << m[i].kolichestvo << endl;
	}
}
void filter_polusharia(coz* m, int count)
{
	char polusharia[32];
	cout << "Введите полушариe: ";
	cin >> polusharia;
	for (int i = 0; i < count; i++)
	{
		if (strcmp(polusharia, m[i].polusharia) == 0)
		{
			cout << endl;
			cout << "название: " << m[i].name << endl;
			cout << " в каких полушариях: " << m[i].polusharia << endl;
			cout << "координаты на небе: " << m[i].koordinati << endl;
			cout << "количество звезд: " << m[i].kolichestvo << endl;
		}
	}
}
int all_stars(coz* f, int count)
{
	int res = 0;
	for (int i = 0; i < count; i++)
	{
		res += f[i].kolichestvo;
	}
	return res;
}

float high_quality(coz* f, int count)
{
	int i_max = 0;
	int ck = 0;
	for (int i = 0; i < count; i++)
	{
		if (ck < f[i].kolichestvo)
		{
			ck = f[i].kolichestvo;
			i_max = i;
		}
	}
	int i_min = 0;
	int min = 0;
	for (int i = 0; i < count; i++)
	{
		if (min > f[i].kolichestvo)
		{
			min = f[i].kolichestvo;
			i_min = i;
		}
	}

	float res = sqrt((powf(int(f[i_max].koordinati) - int(f[i_min].koordinati), 2) + powf((f[i_max].koordinati - int(f[i_max].koordinati)) * 1000 - (f[i_min].koordinati - int(f[i_min].koordinati)) * 1000, 2)));
	return res;
}

void print_menu()
{
	cout << endl;

	cout << "Выберите действие:" << endl;
	cout << "1 - загрузить данные из файла" << endl;
	cout << "2 - вывести данные на экран" << endl;
	cout << "3 - фильтрация полушарию" << endl;
	cout << "4 - расстояние между наибольшим и наименьшим созвездиями" << endl;
	cout << "5 - Сосчитать все звезды в небе" << endl;
	cout << "0 - выход" << endl;
}
// ZhirnovLapin_Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class c_Web
{
public:
	int mul[7][7];
	int weight[7][7];
	int input[7][7];
	const int limit = 100000;
	int sum;
	void Get_Mul();
	void Get_Sum();
	bool Rezult();
	void Load_Weight();
	void Recognize();
	void Study(bool prov, int & endstudy);
	void Inc_Web(int p[7][7]);
	void Dec_Web(int p[7][7]);
	void Get_Input(int ** p);
	c_Web();
};


void c_Web::Get_Input(int ** p)
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			input[i][j] = p[i][j];
}

void c_Web::Get_Mul()
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++) // Пробегаем по каждому аксону
		{
			mul[i][j] = input[i][j] * weight[i][j]; // Умножаем его сигнал (0 или 1) на его собственный вес и сохраняем в массив.
		}
}

void c_Web::Get_Sum()
{
	sum = 0;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			sum += mul[i][j];
}

bool c_Web::Rezult()
{
	if (sum >= limit)
		return true;
	else return false;
}

void c_Web::Load_Weight()
{
	cout << "Enter weight file: ";
	string filename_load;
	cin >> filename_load;
	ifstream load_weight(filename_load);
	

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			load_weight >> weight[i][j];

	load_weight.close();
}

void c_Web::Recognize()
{
	Get_Mul();
	Get_Sum();
	if (Rezult()) 
		cout << " - True, Sum = " << sum << endl;
	else 
		cout << " - False, Sum = " << sum << endl;
}

void c_Web::Study(bool prov, int & endstudy)
{
	Get_Mul();
	Get_Sum();
	if (prov > Rezult())
	{
		endstudy += 1;
		Inc_Web(input);
	}
	else if (prov < Rezult())
	{
		endstudy += 1;
		Dec_Web(input);
	}
}

void c_Web::Inc_Web(int p[7][7])
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			weight[i][j] += p[i][j];
}

void c_Web::Dec_Web(int p[7][7])
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			weight[i][j] -= p[i][j];
}

c_Web::c_Web()
{
}



int main()
{
	int ans;
	while (true)
	{
		cout << " _______________" << endl;
		cout << "| 1 - study     |" << endl;
		cout << "| 2 - recognize |" << endl;
		cout << "| 0_-_exit      |" << endl;
		cout << "|_______________|" << endl << endl;

		cout << "What do you want to do?: ";
		cin >> ans;

		if (ans == 1)
		{
			c_Web myweb;
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 7; j++)
					myweb.weight[i][j] = 0;

			string filenames_God[5];
			for (int i = 0; i < 5; i++)
			{
				filenames_God[i] = "p" + to_string(i+1) + ".txt";
			}

			string filenames_Bad[42];
			for (int i = 0; i < 42; i++)
			{
				filenames_Bad[i] = to_string(i) + ".txt";
			}

			vector<int**> Inputs;
			for (int k = 0; k < 47; k++)
			{
				int** p_mem_input = new int*[7];
				for (int i = 0; i < 7; ++i)
					p_mem_input[i] = new int[7];

				if (k < 42)
				{
					ifstream load_input(filenames_Bad[k]);
					for (int i = 0; i < 7; i++)
						for (int j = 0; j < 7; j++)
						{
							int ch;
							load_input >> ch;
							p_mem_input[i][j] = ch;
						}
					load_input.close();
					Inputs.push_back(p_mem_input);
				}
				else
				{
					ifstream load_input(filenames_God[k - 42]);
					for (int i = 0; i < 7; i++)
						for (int j = 0; j < 7; j++)
							load_input >> p_mem_input[i][j];
					load_input.close();
					Inputs.push_back(p_mem_input);
				}
			}
			int endstudy;
			int round = 0;
			do
			{
				endstudy = 0;
				int k = 0;
				for (auto it : Inputs)
				{
					myweb.Get_Input(it);
					if (k < 42)
					{
						myweb.Study(0, endstudy);
					}
					else
					{
						myweb.Study(1, endstudy);
					}
					k += 1;
				}
				round += 1;
				cout << round << " round completed" << endl;
			} while (endstudy != 0);
			cout << "Studing completed!" << endl;

			cout << "Enter file to save weight: ";
			string filename_save;
			cin >> filename_save;
			ofstream save_weight(filename_save);
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
					save_weight << myweb.weight[i][j] << ' ';
				save_weight << endl;
			}
			save_weight.close();
		}
		else if (ans == 2)
		{
			c_Web myweb;
			myweb.Load_Weight();
			cout << "Enter model file: ";
			string filename_load;
			cin >> filename_load;
			ifstream load_input(filename_load);

			if (load_input.is_open())
			{
				for (int i = 0; i < 7; i++)
					for (int j = 0; j < 7; j++)
						load_input >> myweb.input[i][j];

				load_input.close();

				myweb.Recognize();
			}

		}
		else if (ans == 0)
		{
			return 0;
		}
		else
		{
			cin >> ans;
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.



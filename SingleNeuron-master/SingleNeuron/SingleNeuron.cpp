#include "Neuron.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void print_menu(int& operation)
{
	operation = -1;
	cout << "0. Exit" << endl;
	cout << "1. Study Neuron" << endl;
	cout << "2. Recognize letter" << endl;
	cout << "Your choice: ";
	cin >> operation;
}

// Метод для выгрузки всех матриц из всех файлов
vector<int**> get_letters_matrix_from_file(vector<string> files)
{
	vector<int**> all_matrix;
	for (auto item : files)
	{
		int** matrix = new int* [Neuron::cols];
		for (int c = 0; c < Neuron::cols; c++)
			matrix[c] = new int[Neuron::rows];

		ifstream reader(item);
		if (reader.is_open() == false)
			cout << "File " << item << " doesn't exists" << endl;

		for (int c = 0; c < Neuron::cols; c++)
		{
			for (int r = 0; r < Neuron::rows; r++)
			{
				int symbol;
				reader >> symbol;
				matrix[c][r] = symbol;
			}
		}
		all_matrix.push_back(matrix);
	}

	return all_matrix;
}

void study()
{
	Neuron neuron = Neuron();
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			neuron.weight[c][r] = 0;
		}
	}

	// Записываем все наши имена файлов в вектор
	// < 40 -> Неверные варианты
	// > 40 -> Верные варианты [40..44]
	vector<string> files;
	for (int i = 0; i < 55; i++)
	{
		string filename;
		if (i < 40) filename = "examples/bad/" + to_string(i) + ".txt";
		else filename = "examples/good/e" + to_string(i+1-40) + ".txt";

		files.push_back(filename);
	}

	vector<int**> all_matrix = get_letters_matrix_from_file(files);

	// restudy станет false, если файлы будут распознаны верно
	bool restudy = true;
	int iterations = 0;
	while (restudy)
	{
		int counter = 0;
		for (auto item : all_matrix)
		{
			neuron.setup_input(item);
			if (counter < 40) restudy = !neuron.study(false); // Неверные варианты
			else restudy = !neuron.study(true); // Верные варианты

			counter++;
		}
		cout << "round: " << ++iterations << endl;
	}
	cout << "Study complete." << endl;

	string filename_weight;
	cout << "Enter filename to save weight: ";
	cin >> filename_weight;

	ofstream writer(filename_weight);
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			writer << neuron.weight[c][r] << ' ';
		}
		writer << endl;
	}

	writer.close();
}

void recognize()
{
	Neuron neuron = Neuron();
	if (neuron.load_weight_from_file() == false)
	{
		cout << "Entered weight file doesn't exists" << endl;
		return;
	}

	string image_matrix_filename;
	cout << "Enter filename of image-matrix to recognize: ";
	cin >> image_matrix_filename;

	ifstream reader(image_matrix_filename);
	if (reader.is_open() == false)
	{
		cout << "File doesn't exists" << endl;
		return;
	}

	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			reader >> neuron.input_matrix[c][r];
		}
	}
	reader.close();
	neuron.recognize_letter();
}

int main()
{

	int operation;
	while (true)
	{
		operation = -1;
		print_menu(operation);
		if (operation == 0)
		{
			cout << "Exit" << endl;
			return 0;
		}
		else if (operation == 1)
			study();
		else if (operation == 2)
			recognize();
		else
		{
			cout << "Invalid operation" << endl;
			continue;
		}
	}

	return 0;
}
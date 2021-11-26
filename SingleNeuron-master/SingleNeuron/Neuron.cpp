#include "Neuron.h"
#include <iostream>
#include <fstream>


using namespace std;

// Устанавливаем правильную/неправильную матрицу перед проверкой
void Neuron::setup_input(int** matrix)
{
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			input_matrix[c][r] = matrix[c][r];
		}
	}
}

// Первое, что мы вызываем при обучении и распозновании
//
// Если обучаем то:
// Допустим, что вход получена верная матрица, впервые, на первом кругу из 45 итераций всех наших файлов,
// тогда в аксоне будут все нули, НО, читаем следующее допустим и понимаем, в какой момент появятся единицы
// Допустим, что на вход получена верная матрица, но уже после первого круга из 45 итераций всех файлов,
// после того, как мы их прогнали, в нашем методе study вызывался метод add_weight у верных вариантов, т.к.
// в study приходила информация от нас, что матрица точно верная, при этом нейрон считал, что это не так, срабатывало
// условие true > false и мы прибавляли к весу нейрона, вес верной матрицы.
// Допустим, что на вход получена неверная матрица, а верная еще ни разу не была закинута
// тогда все наши позиции будут нулевыми, все отлично, так быть и должно, дальше поймем почему
// Допустим, что на вход получена все таже неверная матрица, но мы уже закидывали верную, значит у нас уже есть
// какой-то вес, то есть в axon будут записаны только совпадающие единицы неверной матрицы и текущего веса,
// что откинет остальные неправильные единицы, которые могут встречаться в неправильной матрице
void Neuron::get_axon()
{
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			axon[c][r] = input_matrix[c][r] * weight[c][r];
		}
	}
}
// Узнаем сумму весов текущего обучения
void Neuron::get_weight_sum()
{
	sum = 0;
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			sum += axon[c][r];
		}
	}
}

// Проверям, не дошли ли мы до порога, чтобы завершить обучение
// !! Если этот метод вызван из recognize(), то это проверка на то верно ли распознан символ
bool Neuron::check_result()
{
	if (sum >= weight_limit)
		return true;
	else return false;
}

// Просто загружаем вес нейрона из файла
bool Neuron::load_weight_from_file()
{
	string filename;
	cout << "Enter weight filename: ";
	cin >> filename;

	ifstream reader(filename);
	if (reader.is_open() == false)
	{
		cout << "File doesn't exists" << endl;
		return false;
	}

	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			reader >> weight[c][r];
		}
	}
	reader.close();
	return true;
}

// Распознование символа
void Neuron::recognize_letter()
{
	get_axon();
	get_weight_sum();

	if (check_result() == true) cout << "Recognize result: [Successfull], axon sum: [" << sum << "]" << endl;
	else cout << "Recognize result: [Bad], axon sum: [" << sum << "]" << endl;
}

// Возвращает false, если нейросеть ошиблась
// Возвращает true, если сеть поняла символ
void Neuron::study(bool real_result, int& restudy)
{
	get_axon();
	get_weight_sum();

	auto result_from_ai = check_result();
	if (real_result > result_from_ai)
	{
		add_weight(input_matrix);
		restudy += 1;
	}
	else if(real_result < result_from_ai)
	{
		decrease_weight(input_matrix);
		restudy += 1;
	}
}

// Добавляем вес правильной матрицы к весу нейрона
void Neuron::add_weight(int input[7][5])
{
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			weight[c][r] += input[c][r];
		}
	}
}

// Уменьшаем вес нейрона на вес неправильной матрицы
void Neuron::decrease_weight(int input[7][5])
{
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			weight[c][r] -= input[c][r];
		}
	}
}

Neuron::Neuron() {}
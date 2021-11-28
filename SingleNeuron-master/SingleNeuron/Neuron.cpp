#include "Neuron.h"
#include <iostream>
#include <fstream>


using namespace std;

// ”станавливаем правильную/неправильную матрицу перед проверкой
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

// ѕервое, что мы вызываем при обучении и распозновании
//
// ≈сли обучаем то:
// ƒопустим, что вход получена верна€ матрица, впервые, на первом кругу из 55 итераций всех наших файлов,
// тогда в аксоне будут все нули, Ќќ, читаем следующее допустим и понимаем, в какой момент по€в€тс€ единицы
// ƒопустим, что на вход получена верна€ матрица, но уже после первого круга из 55 итераций всех файлов,
// после того, как мы их прогнали, в нашем методе study вызывалс€ метод add_weight у верных вариантов, т.к.
// в study приходила информаци€ от нас, что матрица точно верна€, при этом нейрон считал, что это не так, срабатывало
// условие true > false и мы прибавл€ли к весу нейрона, вес верной матрицы.
// ƒопустим, что на вход получена неверна€ матрица, а верна€ еще ни разу не была закинута
// тогда все наши позиции будут нулевыми
// ƒопустим, что на вход получена все таже неверна€ матрица, но мы уже закидывали верную, значит у нас уже есть
// какой-то вес, то есть в axon будут записаны только совпадающие единицы неверной матрицы и текущего веса,
// что откинет остальные неправильные единицы, которые могут встречатьс€ в неправильной матрице
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
// ”знаем сумму весов текущего обучени€
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

// ѕровер€м, не дошли ли мы до порога, чтобы завершить обучение
// !! ≈сли этот метод вызван из recognize(), то это проверка на то верно ли распознан символ
bool Neuron::check_result()
{
	if (sum >= weight_limit)
		return true;
	else return false;
}

// ѕросто загружаем вес нейрона из файла
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

// –аспознование символа
void Neuron::recognize_letter()
{
	get_axon();
	get_weight_sum();

	if (check_result() == true) cout << "Recognize result: [Successfull], axon sum: [" << sum << "]" << endl;
	else cout << "Recognize result: [Bad], axon sum: [" << sum << "]" << endl;
}

// ¬озвращает false, если нейросеть ошиблась
// ¬озвращает true, если сеть пон€ла символ
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

// ƒобавл€ем вес правильной матрицы к весу нейрона
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

// ”меньшаем вес нейрона на вес неправильной матрицы
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
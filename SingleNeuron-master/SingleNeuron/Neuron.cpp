#include "Neuron.h"
#include <iostream>
#include <fstream>

using namespace std;

// ������������� ����������/������������ ������� ����� ���������
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

// ������, ��� �� �������� ��� �������� � �������������
//
// ���� ������� ��:
// ��������, ��� ���� �������� ������ �������, �������, �� ������ ����� �� 55 �������� ���� ����� ������,
// ����� � ������ ����� ��� ����, ��, ������ ��������� �������� � ��������, � ����� ������ �������� �������
// ��������, ��� �� ���� �������� ������ �������, �� ��� ����� ������� ����� �� 55 �������� ���� ������,
// ����� ����, ��� �� �� ��������, � ����� ������ study ��������� ����� add_weight � ������ ���������, �.�.
// � study ��������� ���������� �� ���, ��� ������� ����� ������, ��� ���� ������ ������, ��� ��� �� ���, �����������
// ������� true > false � �� ���������� � ���� �������, ��� ������ �������.
// ��������, ��� �� ���� �������� �������� �������, � ������ ��� �� ���� �� ���� ��������
// ����� ��� ���� ������� ����� ��������, ��� �������, ��� ���� � ������, ������ ������ ������
// ��������, ��� �� ���� �������� ��� ���� �������� �������, �� �� ��� ���������� ������, ������ � ��� ��� ����
// �����-�� ���, �� ���� � axon ����� �������� ������ ����������� ������� �������� ������� � �������� ����,
// ��� ������� ��������� ������������ �������, ������� ����� ����������� � ������������ �������
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

// ������ ����� ����� �������� ��������
int Neuron::get_weight_sum()
{
	int sum = 0;
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			sum += axon[c][r];
		}
	}
	weight_sum = sum;
	return sum;
}

// ��������, �� ����� �� �� �� ������, ����� ��������� ��������
// !! ���� ���� ����� ������ �� recognize(), �� ��� �������� �� �� ����� �� ��������� ������
bool Neuron::check_result()
{
	if (weight_sum >= weight_limit)
		return true;
	else return false;
}

// ������ ��������� ��� ������� �� �����
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

// ������������� �������
void Neuron::recognize_letter()
{
	get_axon();
	get_weight_sum();

	if (check_result() == true) cout << "Recognize result: [Successfull], axon sum: [" << weight_sum << "]" << endl;
	else cout << "Recognize result: [Bad], axon sum: [" << weight_sum << "]" << endl;
}

// ���������� false, ���� ��������� ��������
// ���������� true, ���� ���� ������ ������
bool Neuron::study(bool real_result)
{
	get_axon();
	get_weight_sum();

	auto result_from_ai = check_result();
	if (real_result > result_from_ai)
	{
		add_weight();
		return false;
	}
	else if(real_result < result_from_ai)
	{
		decrease_weight();
		return false;
	}

	return true;
}

// ��������� ��� ���������� ������� � ���� �������
void Neuron::add_weight()
{
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			weight[c][r] += input_matrix[c][r];
		}
	}
}

// ��������� ��� ������� �� ��� ������������ �������
void Neuron::decrease_weight()
{
	for (int c = 0; c < Neuron::cols; c++)
	{
		for (int r = 0; r < Neuron::rows; r++)
		{
			weight[c][r] -= input_matrix[c][r];
		}
	}
}

Neuron::Neuron() {}
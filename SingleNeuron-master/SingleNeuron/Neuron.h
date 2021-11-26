#ifndef NEURON_H
#define NEURON_H
#include <string>

using namespace std;

class Neuron
{
public:
	static const int cols = 7, rows = 5;
	static const int weight_limit = 100000;
	int weight[cols][rows];
	int input_matrix[cols][rows];
	void get_axon();
	int get_weight_sum();
	bool check_result();
	bool load_weight_from_file();
	void recognize_letter();
	bool study(bool real_result);
	void setup_input(int** p);
	Neuron();

private:
	int axon[cols][rows];
	int weight_sum;
	void add_weight();
	void decrease_weight();
};

#endif
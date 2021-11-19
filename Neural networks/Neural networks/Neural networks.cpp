// Neural networks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "WebE.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void PrintMenu()
{
	cout << "1.Study" << endl
		<< "2.Recognize" << endl
		<< "3.Exit" << endl
		<< "Choice:";
}


int main()
{
	while (1) {
		PrintMenu();
		int x;
		cin >> x;
		switch(x) {
		case 1:
		{
			WebE myweb;                      //clean Web
			for (int i = 0; i <= 4; i++)
				for (int j = 0; j <= 6; j++)
					myweb.weight[i][j] = 0;

		}
		case 2:
		{


		}
		case 3:
		{
			return 0;
			break;
		}
		default:
		{
			cout << "Error" << endl;
		}
		}
		cout << '\n';
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

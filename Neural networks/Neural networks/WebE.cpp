#include "WebE.h"
#include <string>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void WebE::mul_w() //scaled
{
    for (int x = 0; x <= 4; x++)
    {
        for (int y = 0; y <= 6; y++) // for each pix
        {
            mul[x][y] = input[x][y] * weight[x][y]; // �������� ��� ������ (0 ��� 1) �� ��� ����������� ��� � ��������� � ������.
        }
    }
}
void WebE::Sum()
{
    sum = 0;
    for (int x = 0; x <= 4; x++)
    {
        for (int y = 0; y <= 6; y++)
        {
            sum += mul[x][y];
        }
    }
}

 bool WebE::Compare()
{
    if (sum >= limit)
        return true;
    else return false;
}

 void WebE::LoadWeight()
 {
     string filename;
     cout << "Enter filename:";
     cin >> filename;
     ifstream fin(filename);

     for (int i = 0; i < 7; i++)
         for (int j = 0; j < 7; j++)
             fin >> weight[i][j];

     fin.close();
 }

 void WebE::recognize(WebE& myWeb)
 {
     myWeb.mul_w();
     myWeb.Sum();
     if (myWeb.Compare()) listBox1.Items.Add(" - True, Sum = " + Convert.ToString(NW1.sum));
     else listBox1.Items.Add(" - False, Sum = " + Convert.ToString(NW1.sum));
 }
#pragma once
class WebE
{
public:
    int mul[7][7];	//keeping scaled signals
    int weight[7][7]; // keeping weights
    int input[7][7]; // input information 
    int limit = 9; // learning threshold
    int sum; // sum scaled signals
public:
    WebE();  //constructor of object

    void mul_w();

    void Sum();

    bool Compare();

    void LoadWeight();

    void recognize(WebE& myWeb);
    void incW(int inP[5][7]);
    void decW(int inP[5][7]);
};


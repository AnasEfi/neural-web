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
    WebE(int sizex, int sizey, int inP[7][7])     //constructor of object
    {
        weight = new int[7][7];
    }

    void mul_w();

    void Sum();

    bool Compare();

    void LoadWeight();

    void recognize(WebE& myWeb);
};


#include <iostream>
#include <vector>
#include<cmath>
#include"sort.h"


sort::sort(int capital, char attitude)
{
    float wsp=0;
    if(attitude=='')
    {
        //api request
        for(//every brand)
        {


            //algorytmy wyliczające czy firma spełnia zalozenia
            float new_wsp;
            if(new_wsp>wsp)
            {
                brand_name = data.get_stock()
                wsp = new_wsp;
            }
        }
    }
    else
    {
        //else api request

    }

};

bool isrising(const std::vector<double>& inputArray)
{

    double result =0.0;
    if (inputArray.size() < 2) {
        std::cout << "Tablica wejściowa musi mieć co najmniej 2 elementy!" << std::endl;
        return false;
    }

    std::vector<double> currentArray = inputArray;

    while (currentArray.size() > 2) {
        std::vector<double> newArray;

        for (size_t i = 0; i < currentArray.size() - 1; i++) {
            double average = (currentArray[i] + currentArray[i + 1]) / 2;
            newArray.push_back(average);
        }

        currentArray = newArray;
    }

    result = currentArray[1] - currentArray[0];

    if (result>0)
    {
        return true;
    }
    return false ;
};

brand sort::best_match()
{
    return brand(char brand_name);
}

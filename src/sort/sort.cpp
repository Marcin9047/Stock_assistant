#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <string>
#include <fstream>
#include "sort.h"
#include "JsonParser.hpp"
#include "JsonFile.h"

using DataPoint = JsonParser::DataPoint;

sort::sort(int capital, char attitude)
{
    JsonFile file("file.json");
    std::string jsonString = file.read();
    JsonParser parser;
    std::vector<DataPoint> dataPoints = parser.parseJSON(jsonString);
    float wsp=0;
    float new_wsp=0;
    char new_name;
    if(attitude=='low')
    {
        //api request

        for(int i=0;i<1;i++)//for each brand
        {
            if(isrising(parser.getCloseVector(dataPoints)))
            {
                new_wsp++;
            }


            if(new_wsp>wsp)
            {
                wsp = new_wsp;
                brand_name = new_name;
            }
        }
    }
    else
    {
        //else api request

    }

};

double recentdiff(const std::vector<double>& values) {
    int size = values.size();
    if (size < 4) {
        std::cerr << "Wektor musi zawierać przynajmniej 4 wartości!" << std::endl;
        return 0.0;
    }

    double sum = 0.0;
    for (int i = size - 2; i >= size - 4; --i) {
        sum += values[i];
    }
    double average = sum / 3.0;
    double lastValue = values[size - 1];
    double difference = lastValue - average;
    return difference;
}

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

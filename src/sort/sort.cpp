#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <string>
#include <fstream>
#include "sort.h"
#include "JsonParser.hpp"
#include "JsonFile.h"
#include "../api/api.h"
#include "../api/api_cc.h"

using DataPoint = JsonParser::DataPoint;

sort::sort(int capital, char attitude)
{

    if(attitude=='l')
    {
        float g_wsp = 1.0;
        float r_wsp = 2.0;
        float l_wsp = 1.5;
        float wsp=0;
        float new_wsp=0;
        std::string new_name;
        std::string currency="USD";
        std::string crypto="BTC";
        std::string type = "minute";


        for(int i=0;i<1;i++)//for each brand
        {
            ApiCC api;
            api.set_type(type);
            api.set_crypto(crypto);
            api.set_currency(currency);
            std::string jsonString = api.get_data();
            JsonParser parser;
            NASDAQ_pars N_parser;
            std::vector<DataPoint> dataPoints = parser.parseJSON(jsonString);
            std::vector<DataPoint> N_dataPoints = N_parser.parse_NASDAQ(jsonString);
            std::vector<double> close = parser.getCloseVector(dataPoints);

            if(isrising(close))
            {
                new_wsp += r_wsp;
                g_wsp *= recentdiff(close);

                if(islqrise(parser.getVolumeToVector(dataPoints)))
                {
                    new_wsp += (g_wsp-1)*l_wsp;//jeśli funkcja globalnie rosnie to jesli rosnie plynnosc to chcemy by osttatnia wartosc byla w gorca
                }
                else
                {
                    new_wsp += (1-g_wsp)*l_wsp; // jesli funkcja rosnie a lokalnie plynnosc maleje to chcemy by ostatnia wartosc byla w dolku

                }
            }

            if(new_wsp>wsp)
            {
                wsp = new_wsp;
                brand_name.push_back(new_name);
                if(brand_name.size()>3)
                {
                    brand_name.front().erase();
                }
            }
        }
    }
    else
    {
        //else api request
        //else algorithms
        // else wsp

    }

};

double sort::recentdiff(const std::vector<double>& inputArray) {
    int size = inputArray.size();
    if (size < 4) {
        std::cerr << "Wektor musi zawierać przynajmniej 4 wartości!" << std::endl;
        return 0.0;
    }

    double sum = 0.0;
    for (int i = size - 2; i >= size - 4; --i) {
        sum += inputArray[i];
    }
    double average = sum / 3.0;
    double lastValue = inputArray[size - 1];
    double difference = lastValue / average;
    return difference;
}

bool sort::isrising(const std::vector<double>& inputArray)
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

bool sort::islqrise(const std::vector<double>& inputArray)
{
    int size = inputArray.size();
    double sum = 0.0;

    if (size < 4) {
        std::cout << "Tablica wejściowa musi mieć co najmniej 2 elementy!" << std::endl;
        return false;
    }

    for (int i = size - 2; i >= size - 4; --i) {
        sum += inputArray[i];
    }

    double average = sum / 3.0;
    double lastValue = inputArray[size - 1];
    double difference = lastValue - average;
    if(difference>0){
        return true;
    }
    else
    {
        return false;
    }

};
/*
std::vector<brand> sort::best_match()
{
    std::vector<brand> brand_vec
    for (const auto& bn : brand_name) {
           brand_vec.push_back(bn);
        }

    return brand_vec;
}
*/

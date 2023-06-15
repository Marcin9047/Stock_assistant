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

sort::sort(int capital, std::string attitude, std::vector<std::string> favourites)
{
    float risk_wsp = 0.7; //for lowkey *= for cryptocurrencies

    //api get crypto names
    ApiCC api;
    api.set_type("symbols");
    std::string cryptos_names = api.get_data();
    NamePars name_parser;
    std::vector<std::string> cryptos = name_parser.parseNames(cryptos_names);
    std::string currency="USD";
    std::string new_name;

    for(int i=0;i<cryptos.size();i++)//for each brand
    {
        std::string crypto= cryptos[i];
        if(attitude=="lowkey")
        {
            std::string type = "monthly";
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
            float g_wsp = 1.0;  //  recent growth either good or bad
            float r_wsp = 5.0;  // rise == good
            float l_wsp = 1.5;   // liquidity either good or bad
            float h_wsp = 3.0; // hops lower==better (for lowkey)
            float wsp=0;
            float new_wsp=0;

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

                if(hop(parser.getLowVector(dataPoints), parser.getHighVector(dataPoints), parser.getOpenVector(dataPoints), parser.getCloseVector(dataPoints))<0.1)
                {
                    new_wsp += h_wsp;
                }

            }

            new_wsp*=risk_wsp;
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
        else
        {
            std::string type = "minute";
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
            float g_wsp = 2.0;  //  recent growth either good or bad
            float r_wsp = 5.0;  // rise == good
            float l_wsp = 1.5;   // liquidity either good or bad
            float h_wsp = 0.5; // hops higher==better (for risky)
            float wsp=0;
            float new_wsp=0;
            if(isrising(close))
            {
                new_wsp += r_wsp;
                g_wsp *= recentdiff(close);

                if(islqrise(parser.getVolumeToVector(dataPoints)))
                {
                    new_wsp += (g_wsp-2)*l_wsp;//jeśli funkcja globalnie rosnie to jesli rosnie plynnosc to chcemy by osttatnia wartosc byla w gorca
                }
                else
                {
                    new_wsp += (2-g_wsp)*l_wsp; // jesli funkcja rosnie a lokalnie plynnosc maleje to chcemy by ostatnia wartosc byla w dolku

                }

                if(hop(parser.getLowVector(dataPoints), parser.getHighVector(dataPoints), parser.getOpenVector(dataPoints), parser.getCloseVector(dataPoints))<0.5)
                {
                    new_wsp += h_wsp;
                }

            }
            else
            {
                h_wsp *= hop(parser.getLowVector(dataPoints), parser.getHighVector(dataPoints), parser.getOpenVector(dataPoints), parser.getCloseVector(dataPoints));
                g_wsp *= recentdiff(close);
                if(islqrise(parser.getVolumeToVector(dataPoints)))
                {
                    new_wsp += (g_wsp-2)*l_wsp;//jeśli funkcja globalnie nie rosnie to jesli ostatnie wartosci sa w gorce to chcemy by plynnosc rosla gorce
                    new_wsp += h_wsp;
                }
                else
                {
                    new_wsp += (2-g_wsp)*l_wsp; // jesli funkcja nie rosnie a lokalnie plynnosc maleje to chcemy by ostatnia wartosc byla w dolku

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

};

double sort::recentdiff(const std::vector<double>& inputArray) {
    int size = inputArray.size();
    if (size < 4) {
        throw std::invalid_argument("data must have at least 4 sampling periods");
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
        throw std::invalid_argument("data must have at least 2 sampling periods");
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
        throw std::invalid_argument("data must have at least 2 sampling periods");
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

double sort::hop(const std::vector<double>& lowArray, const std::vector<double>& highArray, const std::vector<double>& openArray,const std::vector<double>& closeArray)
{
    if(lowArray.size()!=highArray.size()!=openArray.size()!=closeArray.size())
    {
        throw std::invalid_argument("arrays must be same sizes");
    }

    int size = lowArray.size();
    double wsp;

    for(int i=0;i<size;i++)
    {
        wsp += 2*(highArray[i]-lowArray[i])/(openArray[i]+closeArray[i]);
    }
    wsp /= double(size);

    return wsp;
}

std::vector<brand_crypto> sort::best_match()
{
    std::vector<brand_crypto> brand_vec;
    for (const auto& bn : brand_name) {
            brand_crypto b(bn);
            brand_vec.push_back(b);
        }

    return brand_vec;
}


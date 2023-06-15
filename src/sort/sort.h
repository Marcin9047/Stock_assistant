/*
clasa otrzymująca dane od użytkownika w postaci kapitału, minimalnych zyskow, maksymalnych strat i czasu
na tej podstawie wybiera optymalne firmy
*/
#include <iostream>
#include <vector>
#include "../data/brand.h"

class sort
{
    private:
    std::vector<std::string> brand_name;

    public:
    sort(int capital, std::string attitude, std::vector<brand_crypto> favourites);
    double recentdiff(const std::vector<double> inputArray);
    bool isrising(const std::vector<double> inputArray);
    bool islqrise(const std::vector<double> inputArray);//return true if volumen raisings
    double hop(const std::vector<double> lowArray, const std::vector<double> highArray, const std::vector<double> openArray,const std::vector<double> closeArray);
    std::vector<brand_crypto> best_match();
    // std::string bm(); debug
    // int sizebn();  debug fun


};
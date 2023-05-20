/*
clasa otrzymująca dane od użytkownika w postaci kapitału, minimalnych zyskow, maksymalnych strat i czasu
na tej podstawie wybiera optymalne firmy
*/
#include <iostream>
#include <vector>
//#include "../data/user.h"

class sort
{
    private:
    char brand_name;

    public:
    sort(int capital, char attitude);
    double recentdiff(const std::vector<double>& inputArray);
    bool isrising(const std::vector<double>& inputArray);
    bool islqrise(const std::vector<double>& inputArray);//return true if volumen raisings
//    brand best_match();


};
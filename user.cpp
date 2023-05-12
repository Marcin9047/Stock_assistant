#include "user.h"
#include "brand.h"
#include <vector>
#include <iostream>

user::user(int capital, std::vector<brand> fav, char attitude)
{
    user_capital = capital;
    favourites = fav;
    trading_attitude = attitude;

};

int user::get_capital()
{
    return user_capital;
};

void user::set_capital(int value)
{
    user_capital = value;
};

void user::get_daily_info()
{
};

void user::add_favourite(brand one)
{
    favourites.push_back(one);
};

void user::delate_favourite(char name)
{
    std::vector<brand> new_favourites;
    for (int i=0; i <= favourites.size(); i++)
    {
        if (favourites[i].get_brand() != name)
        {
            new_favourites.push_back(favourites[i]);
        }
    }
    favourites = new_favourites;
};

std::vector<brand> user::get_favourites()
{
    return favourites;
};

brand user::get_suggestions()
{

}
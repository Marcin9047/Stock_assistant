#include "user.h"

user::user(int capital, std::vector<char> fav, char attitude)
{
    user_capital = capital;
    favourites = fav;
    trading_attitude = attitude;

};

int user::grat_capital()
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
    for (int i=0, i <= size(favourite), i++)
    {
        if (favourites[i].get_brand() == name)
        {
            //to be written
        }
    }
};

std::vector<char> user::get_favourites()
{
    return favourites;
};

brand user::get_suggestions()
{

}
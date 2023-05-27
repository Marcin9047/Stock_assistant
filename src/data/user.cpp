#include "user.h"
#include "brand.h"
#include <vector>
#include <iostream>
#include <string>
#include "login.cpp"

user::user(std::string name, std::string login1, std::string password1, int capital)
{
    nickname = name;
    login = login1;
    password = password1;
    user_capital = capital;
    users.push_back(*this);
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

void user::add_favourite(std::string one)
{
    favourites.push_back(one);
};

void user::delate_favourite(std::string name)
{
    std::vector<std::string> new_favourites;
    // for (int i=0; i <= favourites.size(); i++)
    // // {
    // //     if (favourites[i].get_brand() != name)
    // //     {
    // //         new_favourites.push_back(favourites[i]);
    // //     }
    // // }
    favourites = new_favourites;
};

std::vector<std::string> user::get_favourites()
{
    return favourites;
};

std::vector<std::string> user::get_suggestions()
{

};

std::string user::get_name()
{
    return nickname;
};

std::string user::get_login()
{
    return login;
};

std::string user::get_password()
{
    return password;
};
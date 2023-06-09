#pragma once
#include "login.h"
#include <string>


// void operator<<(user_base v1, user player)

void operator%(user_base& v1, user &player)
{
    if (v1.get_users().size() == 0)
        {
        v1.add(player);
        }
    else
    {
        for (int i = 0; i < v1.all_users.size(); i++)
        {
            if (v1.all_users[i].get_name() == player.get_name())
            {
                throw "Podana nazwa użytkownika jest zajęta";  //exeption
            }
            else
                if (v1.all_users[i].get_login() == player.get_login() or v1.all_users[i].get_password() == player.get_password())
                    throw "Podany login lub hasło jest już zajęte";
                else
                    v1.add(player);
                    break;
        };
    };
};

user user_base::log_in(std::string login, std::string password)
{
    for (int i = 0; i < all_users.size(); i++)
    {
        if (all_users[i].get_login() == login && all_users[i].get_password() == password)
        {
            user usr = all_users[i];
            return usr;
        }
    };
    throw "Podana nazwa użytkownika lub hasło jest niepoprawne";
};

std::vector<user> user_base::get_users()
{
    return all_users;
};

void user_base::add(user player)
{
    all_users.push_back(player);
}
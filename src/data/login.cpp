#pragma once
#include "login.h"
#include <string>


// void operator<<(user_base v1, user player)

void operator%(user_base& v1, user &player) // Register
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

user operator<<(user_base& v1, std::vector<std::string>& data) //Log_in
{
    std::vector<user> all_users = v1.get_users();
    for (int i = 0; i < all_users.size(); i++)
    {
        if (all_users[i].get_login() == data[0] && all_users[i].get_password() == data[1])
        {
            user usr = all_users[i];
            usr.change_logged();
            return usr;
        }
    };
    throw "Podana nazwa użytkownika lub hasło jest niepoprawne";
};

void operator>>(user_base& v1, user &player)
{
    player.change_logged();
};



std::vector<user> user_base::get_users()
{
    return all_users;
};

void user_base::add(user player)
{
    all_users.push_back(player);
}
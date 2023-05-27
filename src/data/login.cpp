#pragma once
#include "login.h"
#include <string>

user log_in(std::string login, std::string password)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].get_login() == login && users[i].get_password() == password)
        {
            user usr = users[i];
            return usr;
        }
    };
    throw "Podana nazwa użytkownika lub hasło jest niepoprawne";
}


#include <iostream>
#include <vector>
#include <string>
#pragma once

class user
{
    std::vector<std::string> favourites;
    char trading_attitude;
    int user_capital;
    std::string nickname;
    bool logged = false;


    private:
    protected:
        std::string login;
        std::string password;
    public:
        user(std::string name, std::string login, std::string pasword, int capital = 0);
        int get_capital();
        void set_capital(int value);
        void get_daily_info();
        void add_favourite(std::string one);
        void delate_favourite(std::string name);
        std::vector<std::string> get_favourites();
        std::vector<std::string> get_suggestions();
        bool islogged();
        void change_logged();
        std::string get_name();
        std::string get_login();
        std::string get_password();
};

// class admin: public user
// {

// };

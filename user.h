#include <iostream>
#include <vector>

class user
{
    std::vector<std::string> favourites;
    char trading_attitude;
    int user_capital;

    private:
    public:
        user() = default;
        user(int capital, std::vector<std::string> fav, char attitude);
        int get_capital();
        void set_capital(int value);
        void get_daily_info();
        void add_favourite(std::string one);
        void delate_favourite(std::string name);
        std::vector<std::string> get_favourites();
        std::vector<std::string> get_suggestions();
};

class admin: public user
{

};

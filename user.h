#include <iostream>
#include <vector>

class user
{
    std::vector<brand> favourites;
    char trading_attitude;
    int user_capital;

    private:
    public:
        user() = default;
        user(int capital, std::vector<brand> fav, char attitude);
        int get_capital();
        void set_capital(int value);
        void get_daily_info();
        void add_favourite(brand one);
        void delate_favourite(std::string name);
        std::vector<brand> get_favourites();
        brand get_suggestions();
};

class admin: public user
{

};

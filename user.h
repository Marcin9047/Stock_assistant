#include <iostream>
#include <vector>

class user
{
    std::vector<brand> favourites;
    char trading_attitude;
    int user_capital;

    private:
        int get_capital();
        void set_capital(int value);
    public:
        user(int capital, std::vector<brand> fav, char attitude);
        void get_daily_info();
        void add_favourite(brand one);
        void delate_favourite(char name);
        std::vector<brand> get_favourites();
        brand get_suggestions();
};

class admin: public user
{

};

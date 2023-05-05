#include <iostream>
#include <vector>


class user
{
    std::vector<char> favourites;
    char trading_attitude;
    int user_capital;

    private:
        int get_capital();
        void set_capital(int value);
    public:
        user(int capital, std::vector<char> fav, char attitude);
        user(int capital) = default;
        void get_daily_info();
        void add_favourite(brand one);
        void delate_favourite(char name);
        std::vector<char> get_favourites();
        brand get_suggestions();
}
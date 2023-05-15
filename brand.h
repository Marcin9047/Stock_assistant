#include <istream>
#include <vector>
#include "data.h"

class brand
{
    char brand_name;
    actual_data last_read;
    std::vector<data> history;
    private:
        void clear_before(int time);
    public:
        brand(char name);
        char get_brand();
        void add_raport(data raport);
        float last_value();
        float last_read_time();
        bool is_rising();
    };

class crypto: public brand
{

};

class regular_action: public brand
{

};
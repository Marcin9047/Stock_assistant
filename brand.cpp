#include "brand.h"

brand::brand(char name)
{
    brand_name = name;
};

char brand::get_brand()
{
    return brand_name;
}

void brand::clear_before(int time)
{

};

void brand::add_raport(data raport)
{
    history.push_back(raport);
};

float brand::last_value()
{
    return 0;
};

float brand::last_read_time()
{
    return 0;
};

bool brand::is_rising()
{
    return true;
}
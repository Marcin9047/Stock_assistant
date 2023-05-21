#include "brand.h"
#include <iostream>
#include <string>



brand::brand(std::string name)
{
    brand_name = name;
};

std::string brand::get_brand()
{
    return brand_name;
}

void brand::clear_before(int time)
{

};

void operator<<(brand& b1, data<class T>& d1)
{
    b1.history.push_back(d1);
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
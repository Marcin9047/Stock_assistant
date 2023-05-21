#pragma once
#include <istream>
#include <vector>
#include "data.h"
#include <iostream>
#include <string>

class brand
{
    std::string brand_name;
    data<int> last_read;
    std::vector<data<int>> history;
    private:
        void clear_before(int time);
    public:
        brand(std::string name);
        std::string get_brand();
        friend void operator<<(brand& b1, data & d1);
        float last_value();
        float last_read_time();
        bool is_rising();
    };

// class crypto: public brand
// {

// };

// class regular_action: public brand
// {

// };
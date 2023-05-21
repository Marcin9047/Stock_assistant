#pragma once
#include <istream>
#include <vector>
#include "data.h"
#include <iostream>
#include <string>

template <class T>
class brand
{
    std::string brand_name;
    data<T> last_read;
    std::vector<data<T>> history;
    private:
        void clear_before(int time)
        {

        }
    public:
        brand(std::string name)
        {
            brand_name = name;
        };
        std::string get_brand()
        {
            return brand_name;
        };
        friend void operator<<(brand<T>& b1, data<T> & d1)
        {
            b1.history.push_back(d1);
        };
        float last_value()
        {
            return 0;
        };
        float last_read_time()
        {
            return 0;
        }
        bool is_rising()
        {
            return 0;
        }
    };

typedef brand<int> brand_crypto;
typedef brand<std::string> brand_nasdaq;

// class brand_crypto: public brand
// {

// };

// class regular_action: public brand
// {

// };
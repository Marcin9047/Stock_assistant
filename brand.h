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
            try 
            {
                b1.last_read.get_time();
                b1.history.push_back(b1.last_read);
                b1.last_read = d1;
            }
            catch (...)
            {
                b1.last_read = d1;
            };
            
        };
        float last_value()
        {
            return last_read.get_close();
        };
        int last_read_time()
        {
            return last_read.get_time();
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
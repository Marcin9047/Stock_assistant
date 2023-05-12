#include "data.h"

data::data(char stock, int time, float high,
        float low, float open, float vol_from,
        float vol_to, float close, char conversion)
        {
           stock_name = stock;
           conversionType = conversion;
           high_value = high;
           low_value = low;
           open_value = open;
           close_value = close;
           volume_from = vol_from;
           volume_to = vol_to;
        };

char data::get_stock()
{
    return stock_name;
};

int data::get_time()
{
    return read_time;
};

float data::get_high_value()
{
    return high_value;
};

float data::get_low_value()
{
    return low_value;
};
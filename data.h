#pragma once
#include <istream>

template <class T>
class data
{
T read_time;
float high_value;
float low_value;
float open_value;
float volume_from;
float volume_to;
float close_value;
char conversionType;     
private:
public:
    data() = default;
    data(T time, float high, float low, float open, float vol_from,
    float vol_to, float close, char conversion)
    {
            read_time = time;
           conversionType = conversion;
           high_value = high;
           low_value = low;
           open_value = open;
           close_value = close;
           volume_from = vol_from;
           volume_to = vol_to;
    }
    T get_time()
    {
        return read_time;
    };
    float get_high_value()
    {
        return high_value;
    };
    float get_low_value()
    {
        return low_value;
    };
};



class crypto_data : public data<int>
{
public:
    crypto_data() = default;

    crypto_data(int time, float high, float low, float open, float vol_from,
                float vol_to, float close, char conversion)
        : data<int>(time, high, low, open, vol_from, vol_to, close, conversion)
    {
    };
};



class nasdaq_data: public data<std::string>
{
    private:
        
    public:
        int converted_time();

};

// class historic_data: public data
// {
//     private:
//         void clear(); // Czyści zawartość starego rejestru
//     public:
//         void write_to_file(); //Zapisuje do rejestru
// };
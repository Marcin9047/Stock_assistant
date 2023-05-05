#include <istream>


class data
{
char stock_name;
int read_time;
float high_value;
float low_value;
float open_value;
float volume_from;
float volume_to;
float close_value;
char conversionType;     
private:
public:
    data(char stock, int time, float high,
        float low, float open, float vol_from,
        float vol_to, float close, char conversion);
    char get_stock();
    int get_time();
    float get_high_value();
    float get_low_value();
};
#ifndef API_NASDAQ_H
#define API_NASDAQ_H

#include "api.h"

class ApiNasdaq: public Api
{
public:
    ApiNasdaq(/* args */);
    // void set_type(std::string new_type);
    // void set_crypto(std::string new_crypto);
    // void set_currency(std::string new_currency);

private:
    // std::string type;
    // std::string crypto; 
    // std::string currency;
    // std::string limit = "2000";
    std::map<std::string, std::string> urls;
    void create_url() override;
};


#endif
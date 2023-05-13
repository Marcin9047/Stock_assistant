#ifndef API_CC_H
#define API_CC_H

#include "api.h"

class ApiCC: public Api
{
public:
    ApiCC(/* args */);
    void set_type(std::string new_type);
    void set_crypto(std::string new_crypto);
    void set_currency(std::string new_currency);

private:
    std::string type;
    std::string crypto; 
    std::string currency;
    int limit = 2000;
    std::map<std::string, std::string> urls;
    std::string create_url() override;
};


#endif
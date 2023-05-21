#ifndef API_NASDAQ_H
#define API_NASDAQ_H

#include "api.h"

class ApiNasdaq: public Api
{
public:
    ApiNasdaq(/* args */);
    void set_type(std::string new_type);
    void set_company(std::string new_company);
    void set_database(std::string new_database);

private:
    std::string type;
    std::string company;
    std::string database;
    std::map<std::string, std::string> urls;
    void create_url() override;
};


#endif
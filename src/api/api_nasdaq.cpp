#include "api_nasdaq.h"

ApiNasdaq::ApiNasdaq()
{
    urls = {
        {"NASDAQ", "https://data.nasdaq.com/api/v3/"},
        {"databases", "databases"},
    };
}

void ApiNasdaq::set_type(std::string new_type) {
    // if(new_type.empty()) {
    //     throw std::invalid_argument("Type cannot be empty");
    // } else if(urls.find(new_type) == urls.end() && new_type != "crypto compare") {
    //     throw std::invalid_argument("Invalid type: " + new_type);
    // }
    type = new_type;
}

void ApiNasdaq::set_database(std::string new_database) {
    database = new_database;
}

void ApiNasdaq::set_company(std::string new_company)
{
     if(new_company.empty()) {
        throw std::invalid_argument("Company cannot be empty");
    }
    company = new_company;
}

void ApiNasdaq::create_url() {
    url = urls["NASDAQ"];
    if (type == "databases"){
        url += type;
    } else {
        url += "datasets/" + database + "/";
        url += company + "/data.json";
    }
    
    
    url += "?api_key=" + keys["NASDAQ_API_Key"];
    // url += "&start_date=2020-01-01&end_date=2020-12-31";
}

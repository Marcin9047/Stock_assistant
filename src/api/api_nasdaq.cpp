#include "api_nasdaq.h"

ApiNasdaq::ApiNasdaq()
{
    urls = {
        
    };
}

// void ApiCC::set_type(std::string new_type)
// {
//     type = new_type;
// }

// void ApiCC::set_crypto(std::string new_crypto)
// {
//     crypto = new_crypto;
// }

// void ApiCC::set_currency(std::string new_currency)
// {
//     currency = new_currency;
// }

void ApiNasdaq::create_url() {
    url = "";
    url += urls["nasdaq"];

    
    

    log_event(url);
}

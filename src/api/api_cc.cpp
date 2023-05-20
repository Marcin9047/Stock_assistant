#include "api_cc.h"

ApiCC::ApiCC()
{
    urls = {
        {"crypto compare", "https://min-api.cryptocompare.com/data/"},
        {"single", "price?"},
        {"multi", "pricemulti?"},
        {"daily", "v2/histoday?"},
        {"hourly", "v2/histohour?"},
        {"minute", "v2/histominute?"},
        {"symbols", "all/coinlist?summary=true"},
    };
}

void ApiCC::set_type(std::string new_type)
{
    if(new_type.empty()) {
        throw std::invalid_argument("Type cannot be empty");
    } else if(new_type != "single" && new_type != "multi" && new_type != "daily" 
        && new_type != "hourly" && new_type != "minute" && new_type != "symbols") {
        throw std::invalid_argument("Invalid type: " + new_type);
    }
    type = new_type;
}

void ApiCC::set_crypto(std::string new_crypto)
{
    if(new_crypto.empty()) {
        throw std::invalid_argument("Crypto cannot be empty");
    }
    crypto = new_crypto;
}

void ApiCC::set_currency(std::string new_currency)
{
    if(new_currency.empty()) {
        throw std::invalid_argument("Currency cannot be empty");
    }
    currency = new_currency;
}


void ApiCC::create_url() {
    url = urls["crypto compare"] + urls[type];

    if (type == "single") {
        url += "fsym=" + crypto + "&tsyms=" + currency;
    } else if (type == "multi") {
        url += "fsyms=" + crypto + "&tsyms=" + currency;
    } else if (urls[type].find("histo") != std::string::npos) {
        url += "fsym=" + crypto + "&tsym=" + currency;
        // url += "&limit=" + limit;
        url += "&toTs=";
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        url += std::to_string(now_time_t);
    }

    // url += "&api_key=" + keys["cc_API_Key"];

}

#include "api_cc.h"

ApiCC::ApiCC()
{
    urls = {
        {"crypto compare", "https://min-api.cryptocompare.com/data/"},
        {"single","price?"},
        {"multi","pricemulti?"},
        {"daily", "v2/histoday?"},
        {"hourly", "v2/histohour?"},
        {"minute", "v2/histominute?"},
    };
}

void ApiCC::set_type(std::string new_type)
{
    type = new_type;
}

void ApiCC::set_crypto(std::string new_crypto)
{
    crypto = new_crypto;
}

void ApiCC::set_currency(std::string new_currency)
{
    currency = new_currency;
}

std::string ApiCC::create_url() {
    std::string url = "";
    url += urls["crypto compare"] + urls[type];

    if (type == "single") {
        url += "fsym=" + crypto + "&tsyms=";
    } else if (type == "multi") {
        url += "fsyms=" + crypto + "&tsyms=";
    } else if (urls[type].find("histo") != std::string::npos) {
        url += "fsym=" + crypto + "&tsym=";
    }

    url += currency;
    
    // url += keys["cc_API_Key"];
    return url;
}

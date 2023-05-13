#include "api.h"

API::API() {
    // For more information about api:
    // https://min-api.cryptocompare.com/documentation
    // https://data.nasdaq.com/tools/api

    urls = {
        {"crypto compare", "https://min-api.cryptocompare.com/data/"},
        {"single","price?"},
        {"multi","pricemulti?"},
        {"daily", "v2/histoday?"},
        {"hourly", "v2/histohour?"},
        {"minute", "v2/histominute?"},
        
        // keys below are private and need to be changed before going public
        {"cc_API_Key", "9c4354165cddf934ea4f93cb003060ff783d64e074bb3065f8dce7b999d49ba7"},
        {"NASDAQ_API_Key", "iSWZmxQeJPXMNLrpiBrf"}
    };
}

std::string API::get_data(std::string type, std::string crypto, std::string currency) {
    std::string url = create_url(type, crypto, currency);
    return data_from_url(url);
}

std::string API::create_url(std::string type, std::string crypto, std::string currency) {
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
    
    // url += urls["cc_API_Key"];
    return url;
}

size_t API::writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string API::data_from_url(std::string url) {
    CURL *curl = curl_easy_init();
    if(curl) { 
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return response_string;
    }
    return "error in api data";
}

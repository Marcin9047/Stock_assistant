#include <iostream>
#include <string>
#include <map>
#include <curl/curl.h>

// For more information about api:
// https://min-api.cryptocompare.com/documentation

std::map <std::string, std::string> urls = {
    {"crypto compare", "https://min-api.cryptocompare.com/data/"},
    {"single","price?"},
    {"multi","pricemulti?"},
    {"daily", "v2/histoday?"},
    {"hourly", "v2/histohour?"},
    {"minute", "v2/histominute?"},
    {"API_Key", "9c4354165cddf934ea4f93cb003060ff783d64e074bb3065f8dce7b999d49ba7"}
};



size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string create_url(std::string type, std::string crypto, std::string currency) {
    std::string url = "";
    url += urls["crypto compare"] + urls[type];

    if (type == "single") {
        url += "fsym="+ crypto + "&tsyms=";
    } else if (type == "multi") {
        url += "fsyms=" + crypto + "&tsyms=";
    } else if (urls[type].find("histo") != std::string::npos) {
        url += "fsym="+ crypto + "&tsym=";
    }

    url += currency;
    
    // url += urls["API_Key"];
    return url;
}

std::string data_from_url(std::string url) {
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

int main() {
    std::string url = create_url("multi","BTC","USD");
    std::cout << data_from_url(url) << "\n" << std::endl;
}

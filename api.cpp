#include <iostream>
#include <string>
#include <map>
#include <curl/curl.h>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string data_from_url() {
    std::string cryp_compare = "https://data-api.cryptocompare.com/";
    CURL *curl = curl_easy_init();
    if(curl) {
        std::string url = cryp_compare + "data/tradingsignals/intotheblock/latest?fsym=BTC";
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
    std::cout << data_from_url() << "\n" << std::endl;
}

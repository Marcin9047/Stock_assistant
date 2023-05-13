#ifndef API_H
#define API_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <curl/curl.h>

class API {
public:
    API();
    std::string get_data(std::string type, std::string crypto, std::string currency);

private:
    std::map<std::string, std::string> urls;

    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);
    std::string create_url(std::string type, std::string crypto, std::string currency);
    std::string data_from_url(std::string url);
};

#endif

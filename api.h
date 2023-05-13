#ifndef API_H
#define API_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <curl/curl.h>

class Api {
public:
    Api();
    std::string get_data();

private:
    std::map<std::string, std::string> keys;
    virtual std::string create_url();
    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);
    std::string data_from_url(std::string url);
};

#endif

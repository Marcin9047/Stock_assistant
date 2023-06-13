#ifndef API_H
#define API_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <memory>
#include <iomanip>
#include <ctime>
#include <sys/stat.h>
#include <curl/curl.h>

class Api {
public:
    Api(std::string new_url = "");
    virtual ~Api() = default;
    std::string get_data();
    void save_data_to_json();

protected:
    std::string url;
    std::map<std::string, std::string> keys;
    std::string log_path = "log/api_log.txt";
    void log_event(const std::string& line);

private:
    virtual void create_url();
    std::string data_from_url();
    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);
};

class CurlDeleter {
public:
    void operator()(CURL* curl) {
        curl_easy_cleanup(curl);
    }
};
#endif

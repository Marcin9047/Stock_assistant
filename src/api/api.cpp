#include "api.h"

Api::Api(std::string new_url)
{
    if (!new_url.empty())
    {
        url = new_url;
    }    

    // For more information about api:
    // https://min-api.cryptocompare.com/documentation
    // https://data.nasdaq.com/tools/api

    keys = {
        // Keys below are private and need to be changed before going public
        {"cc_API_Key", "9c4354165cddf934ea4f93cb003060ff783d64e074bb3065f8dce7b999d49ba7"},
        {"NASDAQ_API_Key", "iSWZmxQeJPXMNLrpiBrf"}
    };
}

std::string Api::get_data() {
    return data_from_url();
}

void Api::create_url(){
    // Overrided in subclasses
};

size_t Api::writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string Api::data_from_url() {
    if (url.empty()) {
        create_url();
    }

    std::unique_ptr<CURL, CurlDeleter> curl(curl_easy_init());
    if(curl) {
        std::string response_string;
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_string);
        CURLcode res = curl_easy_perform(curl.get());
        if(res != CURLE_OK) {
            throw std::runtime_error(std::string("curl_easy_perform() failed: ") 
                                     + curl_easy_strerror(res));
        }

        long response_code;
        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &response_code);
        if(response_code >= 400) {
            throw std::runtime_error("HTTP error: " + std::to_string(response_code));
        }

        return response_string;
    }
    throw std::runtime_error("Failed to initialize cURL");
}

void Api::save_data_to_json(){
    std::ofstream file("file.json");
    file << data_from_url();
    file.close();
}

void Api::save_url_to_log(const std::string &fileName, const std::string &line)
{
    struct stat info;
    if(stat("log", &info) != 0 || !(info.st_mode & S_IFDIR)) {
        system("mkdir log");
    }

    std::ofstream file(fileName, std::ios::app);
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    file << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] " << line << std::endl;
}

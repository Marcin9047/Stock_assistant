#include "api.h"

Api::Api(std::string new_url)
{
    if (new_url != "")
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
    if (url == "")
    {
        create_url();
    }

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
    return "error in api data_from_url()";
}

void Api::save_data_to_json(){
    std::ofstream file("file.json");
    file << data_from_url();
    file.close();
}

void Api::save_url_to_log(const std::string &fileName, const std::string &line)
{
    std::ofstream file(fileName, std::ios::app);
    file << line << std::endl;
}

#include <iostream>
#include <fstream>
#include <string>
#include "login.h"
#include <sstream>
#include <nlohmann/json.hpp>
#include "brand.h"



std::string toJsonString(const std::string& key, const std::string& value) {
    return "\"" + key + "\": \"" + value + "\"";
}

void user_base::writeJsonToFile() {
    std::ofstream file(name + ".json");
    if (file.is_open()) {
        file << "{\n";
        for (long unsigned int i = 0; i < all_users.size(); i++)
        {   
            file << "\"" + all_users[i].get_name() + "\""  << ":";
            file << "{\n";
            file << "\t" << toJsonString("login", all_users[i].get_login()) << ",\n";
            file << "\t" << toJsonString("password", all_users[i].get_password()) << ",\n";
            file << "\t" << toJsonString("capital", std::to_string(all_users[i].get_capital())) << ",\n";

             std::stringstream ss;
            for (const auto& one : all_users[i].get_favourites()) {
                ss << one << " ";
            }
            std::string favouritesString = ss.str();


            file << "\t" << toJsonString("favorites", favouritesString) << "\n";
        if (i != all_users.size() - 1)
            file << "}, \n";
        else
            file << "} \n";
        };
        file << "}";
        file.close();
        std::cout << "Data written to " << name + ".json" << std::endl;
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}

using json = nlohmann::json;

bool loadJSONFromFile(const std::string& filename, json& jsonData) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> jsonData;
        file.close();
        return true;
    } else {
        return false;
    }
}

void user_base::LoadFromJson() {


    std::ifstream file(name + ".json");
    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    json jsonData = json::parse(jsonString);

  if (jsonData.is_object()) {
    // Iterate over each object within the JSON
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        std::string key = it.key();
        json obj = it.value();

        // Access the properties of each object
        std::string login = obj["login"].get<std::string>();
        std::string password = obj["password"].get<std::string>();
        std::string capital = obj["capital"].get<std::string>();
        std::string favorites = obj["favorites"].get<std::string>();

        // Print the values
        user u1(key, login, password, std::stoi(capital));
        
        

    // Create a stringstream object and initialize it with the sentence
    std::istringstream iss(favorites);

    std::string word;
    while (iss >> word) {
        // Remove any leading or trailing punctuation marks
        // (modify this part according to your requirements)
        while (!word.empty() && !isalnum(word.front())) {
            word.erase(0, 1);
        }
        while (!word.empty() && !isalnum(word.back())) {
            word.pop_back();
        }

        brand_crypto b1(word);
        u1.add_favourite(word);
    }
    add(u1);
    }
        std::cout << std::endl;
    std::cout << "Data loaded from " << name + ".json" << std::endl;
    } 
    else
    {
        std::cout << "Unable to open file." << std::endl;
    };
}



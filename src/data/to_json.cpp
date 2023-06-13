#include <iostream>
#include <fstream>
#include <string>
#include "login.h"
#include <sstream>


std::string toJsonString(const std::string& key, const std::string& value) {
    return "\"" + key + "\": \"" + value + "\"";
}

void user_base::writeJsonToFile() {
    std::ofstream file("name1.json");
    if (file.is_open()) {
        for (long unsigned int i = 0; i < all_users.size(); i++)
        {
            file << "{\n";
            file << "\t" << toJsonString("name", all_users[i].get_name()) << ",\n";
            file << "\t" << toJsonString("login", all_users[i].get_login()) << ",\n";
            file << "\t" << toJsonString("password", all_users[i].get_password()) << ",\n";
            file << "\t" << toJsonString("capital", std::to_string(all_users[i].get_capital())) << ",\n";


             std::stringstream ss;
            for (const auto& one : all_users[i].get_favourites()) {
                ss << one << " ";
            }
            std::string favouritesString = ss.str();


            file << "\t" << toJsonString("favorites", favouritesString) << "\n";
            file << "}";
        };
        file.close();
        std::cout << "Data written to " << name << std::endl;
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}






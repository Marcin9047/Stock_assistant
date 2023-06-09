#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class JsonFile {
public:
    JsonFile(std::string filename);
    std::string  read();
    void write(std::string filename);
private:
    std::string m_filename;

};

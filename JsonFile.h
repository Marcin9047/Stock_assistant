#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class JsonFile {
public:
    JsonFile(std::string filename) : m_filename(filename) {}

    void read(json& j);
    void write(const json& j);
private:
    std::string m_filename;
};

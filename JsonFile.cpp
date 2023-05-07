#include <iostream>
#include <fstream>
#include"JsonFile.h"

using json = nlohmann::json;


void JsonFile::read(json& j)
{
    std::ifstream file(m_filename);
    if (!file) {
        std::cerr << "Failed to open file " << m_filename << std::endl;
        return false;
    }

    try {
        file >> j;
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON from file " << m_filename << ": " << e.what() << std::endl;
        return false;
    }

    return true;
}

void JsonFile::write(const json& j)
{
    std::ofstream file(m_filename);
    if (!file) {
        std::cerr << "Failed to open file " << m_filename << " for writing" << std::endl;
        return false;
    }

    try {
        file << std::setw(4) << j;
    } catch (const std::exception& e) {
        std::cerr << "Failed to serialize JSON to file " << m_filename << ": " << e.what() << std::endl;
        return false;
    }

    return true;
}


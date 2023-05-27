#include <iostream>
#include <fstream>
#include "JsonFile.h"
#include "json.hpp"

using json = nlohmann::json;

JsonFile::JsonFile(std::string filename)
{
    m_filename = filename;
}
std::string JsonFile::read()
{
    std::ifstream file(m_filename);
    if (!file)
    {
        std::cerr << "Failed to open file " << m_filename << std::endl;
        return "";
    }

    json j;
    file >> j;

	return j.dump(4);

}

void JsonFile::write(std::string filename)
{
    std::ofstream output_file(filename);
    if (!output_file)
    {
        std::cerr << "Failed to open file " << m_filename << std::endl;
        return;
    }


    output_file << read()<< std::endl;
}


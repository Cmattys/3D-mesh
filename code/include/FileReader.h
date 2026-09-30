#pragma once

#include <string>
#include <fstream>

class FileReader {
private:
    std::string filename;
    std::ifstream fileStream;

public:
    FileReader(const std::string& file_name);

    std::string Readline();
};
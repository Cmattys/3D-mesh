#pragma once
#include <vector>
#include "FileReader.h"

class Fill_Vector
{
private:
    std::vector<float> Point;
    std::vector<int> Face;
    FileReader& reader;
public:
    Fill_Vector(FileReader& reader_name);
    void export_data();
};


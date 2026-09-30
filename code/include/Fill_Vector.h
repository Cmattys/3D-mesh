#pragma once
#include <vector>
#include "FileReader.h"

class Fill_Vector
{
private:
    std::vector<float> Point;
    int Vertex_count;
    std::vector<int> Face;
    int Face_count;
    FileReader& reader;
    void export_size();
public:
    Fill_Vector(FileReader& reader_name);
    void export_data();
};


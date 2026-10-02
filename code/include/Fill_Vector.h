#pragma once
#include <vector>
#include <array>
#include "FileReader.h"

class Fill_Vector
{
private:
    std::vector<std::array<float,3>> Point;
    int Vertex_count;
    std::vector<std::array<int,3>> Face;
    int Face_count;
    FileReader& reader;
    void export_size();
public:
    Fill_Vector(FileReader& reader_name);
    void export_data();
};


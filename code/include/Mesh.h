#pragma once

#include<iostream>
#include <array>
#include <vector>
#include "HalfEdge.h" // Tes classes Vertex, Face, HalfEdge

class Mesh {
private:
    std::vector<Vertex*> tabVertex;
    std::vector<Face*> tabFace;
    std::vector<HalfEdge*> tabHE;

public:
    Mesh(const std::vector<std::array<float, 3>>& V, const std::vector<std::array<int, 3>>& F);
    const std::vector<Vertex*>& getVertices() const { return tabVertex; }
    const std::vector<Face*>& getFaces() const { return tabFace; }
    ~Mesh();
};

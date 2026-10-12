#pragma once


#include <vector>

// 1. Déclarations anticipées indispensables
class Vertex;
class Face;
class HalfEdge;

// 2. Définition des classes
class Vertex {
public:
    double x, y, z;
    HalfEdge* he = nullptr;
};

class Face {
public:
    HalfEdge* he = nullptr;
};

class HalfEdge {
public:
    Vertex* target = nullptr;
    HalfEdge* twin = nullptr;
    HalfEdge* next = nullptr;
    Face* face = nullptr;
};

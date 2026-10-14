#include <iostream>
#include "FileReader.h"
#include "Fill_Vector.h"
#include "Mesh.h"



int main() {
    // 1. Création de l'objet FileReader avec le nom de ton fichier
    FileReader lecteur("../Fichier_obj/jointure_v2.obj");
    Fill_Vector Tab (lecteur);
    Tab.export_data();
    const std::vector<std::array<float,3>>& points = Tab.getPoints();
    const std::vector<std::array<int,3>>& faces = Tab.getFaces();
    Mesh Me (points,faces);
    return 0;
}
#include <iostream>
#include "FileReader.h"
#include "Fill_Vector.h"

int main() {
    // 1. Création de l'objet FileReader avec le nom de ton fichier
    FileReader lecteur("../Fichier_obj/vaze2.OBJ");
    Fill_Vector Tab (lecteur);
    Tab.export_data();
    return 0;
}
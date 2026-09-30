#include <iostream>
#include "FileReader.h"

int main() {
    // 1. Création de l'objet FileReader avec le nom de ton fichier
    FileReader lecteur("../Fichier_obj/vaze2.OBJ");
    std::string ligne_actuelle;
    std::cout << "--- Début de la lecture ---" << std::endl;
        ligne_actuelle = lecteur.Readline();
        std::cout<<ligne_actuelle << std::endl;
        ligne_actuelle = lecteur.Readline();
        std::cout<<ligne_actuelle << std::endl;
        ligne_actuelle = lecteur.Readline();
        std::cout<<ligne_actuelle << std::endl;
        ligne_actuelle = lecteur.Readline();
        std::cout<<ligne_actuelle << std::endl;
    std::cout << "--- Fin de la lecture ---" << std::endl;
    return 0;
}
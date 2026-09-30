#include "FileReader.h"
#include <iostream>

FileReader::FileReader(const std::string& file_name) : filename(file_name){
    fileStream.open(filename);
    if (!fileStream.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
    }
}

std::string FileReader::Readline() {
    std::string line;
    
    // std::getline renvoie true tant qu'il arrive à lire une ligne
    if (fileStream.is_open() && std::getline(fileStream, line)) {
        return line;
    }
    // Utile pour que lorsque l'on utilise la fonction on sache quand s'arreter
    return "<FIN_DE_FICHIER>"; 
}
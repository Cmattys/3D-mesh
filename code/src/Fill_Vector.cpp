#include "Fill_Vector.h"
#include "FileReader.h"
#include <vector>
#include<iostream>

Fill_Vector::Fill_Vector(FileReader& reader_name) : reader(reader_name){

}

void Fill_Vector::export_size(){
    std::string current_line;
    std::string keyword = "Vertex";
    std::string number = "0123456789";
    bool etat = true;

    // on vas chercher la ligne avec écrit Vertex pour recuperer le nombre totel de Vertex
    while (etat){
        current_line = reader.Readline();
        if(current_line.find(keyword) != std::string::npos){
            etat=false;
        }
    }
    // on vas chercher la position du premier chiffre de la ligne avec find
    int pos = current_line.find_first_of(number);
    // on creer un sous str a partir du premeir chiffre et transforme ce str en int
    Vertex_count = std::stoi(current_line.substr(pos));
    std::cout<<"Vertex : "<<Vertex_count<<std::endl;
    Point.resize(Vertex_count);
    // On fait la meme chose avec les face
    keyword = "Face";
    etat = true;
    while (etat){
        current_line = reader.Readline();
        if(current_line.find(keyword) != std::string::npos){
            etat=false;
        }
    }
    pos = current_line.find_first_of(number);
    Face_count = std::stoi(current_line.substr(pos));
    std::cout<<"Face : "<<Face_count<<std::endl;
    Face.resize(Face_count);
}
void Fill_Vector::export_data(){
    //std::string current_line = reader.Readline();
    export_size();
}
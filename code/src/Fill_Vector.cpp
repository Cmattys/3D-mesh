#include "Fill_Vector.h"
#include "FileReader.h"
#include <vector>
#include <array>
#include<iostream>

Fill_Vector::Fill_Vector(FileReader& reader_name) : reader(reader_name){

}

void Fill_Vector::export_size(){
    std::string current_line;
    std::string keyword = "Vertices";
    std::string number = "0123456789";
    bool etat = true;

    // on vas chercher la ligne avec écrit Vertices pour recuperer le nombre totel de Vertex
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
    keyword = "Faces";
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
    export_size();
    std::string current_line = " ";
    // le caractere v en debut de ligne nous indique qu'on a les info d'un Vertex
    while (current_line[0]!='v'){
        current_line=reader.Readline();
    }
    //Vérif qu'on a bien trouver une ligne de Vertex

    //std::cout<<"premiere lettre : "<<current_line[0]<<std::endl;

    //Déclaration de variables
    int space1,space2,space3;
    std::string str_x,str_y,str_z;
    float x,y,z;


    for(int i=0;i<Vertex_count;i++){

    // on cherche les espaces qui sépare les coordonnées des Vertex
        space1 = current_line.find(' ');
        space2 = current_line.find(' ', space1+1 ); //le space1+1 permet d'indiquer de chercher a partir de la pos space1+1
        space3 = current_line.find(' ', space2+1 );
    
        //on crée des sous string qui contienne ce qu'il y a entre les espaces
        str_x = current_line.substr(space1 + 1, space2 - space1 - 1);
        str_y = current_line.substr(space2 + 1, space3 - space2 - 1);
        str_z = current_line.substr(space3 + 1);

        //transformation des string en float
        x = std::stof(str_x);
        y = std::stof(str_y);
        z = std::stof(str_z);

        //On remplie notre vector de vertex et on passe a la ligne suivante
        Point[i]= {x,y,z};
        current_line=reader.Readline();
    }

    //Debugage 
    
    std::cout<<"x : " <<Point[0][0]<<std::endl;
    std::cout<<"y : " <<Point[0][1]<<std::endl;
    std::cout<<"z : " <<Point[0][2]<<std::endl;
    

    // On fait la même chose pour les faces
    while (current_line[0]!='f'){
        current_line=reader.Readline();
    }
    //Debug
    //std::cout<<"premiere lettre : "<<current_line[0]<<std::endl;

    int f1,f2,f3;
    for(int i=0;i<Face_count;i++){
        space1 = current_line.find(' ');
        space2 = current_line.find(' ', space1+1 );
        space3 = current_line.find(' ', space2+1 );

        str_x = current_line.substr(space1 + 1, space2 - space1 - 1);
        str_y = current_line.substr(space2 + 1, space3 - space2 - 1);
        str_z = current_line.substr(space3 + 1);

        f1 = std::stoi(str_x);
        f2 = std::stoi(str_y);
        f3 = std::stoi(str_z);

        Face[i]= {f1,f2,f3};
        current_line=reader.Readline();
    }
    //Debug
    /*
    std::cout<<"F1 : " <<Face[825][0]<<std::endl;
    std::cout<<"F2 : " <<Face[825][1]<<std::endl;
    std::cout<<"F3 : " <<Face[825][2]<<std::endl;
    */
}
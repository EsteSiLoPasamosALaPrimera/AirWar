//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_ENEMIGO_H
#define AIRWAR_ENEMIGO_H
#include<iostream>
#include <allegro5/bitmap.h>
#include "fstream"

using namespace std;

class Enemigo{
public:
    int posX;
    int posY;
    int velocidad;
    int ataque;
    int resistencia;

    void descargar(bool iteracion);
    void moverse();

    Enemigo();
    ~Enemigo();
    ALLEGRO_BITMAP* imagen=NULL;

protected:
    string id=typeid(Enemigo).name();

};

Enemigo::Enemigo() {
    posX=posY=0;
    ataque=0;
    velocidad=0;
    resistencia=0;
    imagen=NULL;
}

void Enemigo::descargar(bool iteracion) {
    string info=id+";"+to_string(resistencia)+";"+to_string(posX)+";"+to_string(posY)+";\n";
    if(iteracion==true){
        ofstream archivo("/home/alfredo/Inicio/Documentos/torres.txt");
        archivo<<info;
        archivo.close();
    }else{
        ofstream archivo("/home/alfredo/Inicio/Documentos/torres.txt",ios::app);
        archivo<<info;
        archivo.close();
    }
}

Enemigo::~Enemigo() {
    //al_destroy_bitmap(imagen);
}

void Enemigo::moverse() {
    posY+=velocidad;
}
#endif //AIRWAR_ENEMIGO_H

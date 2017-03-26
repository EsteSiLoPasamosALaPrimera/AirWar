//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORRE_H
#define AIRWAR_TORRE_H

#include <iostream>
#include <allegro5/allegro.h>
#include "Enemigo.h"

using namespace std;

class Torre : public Enemigo{
public:
    Torre();
    Torre(int pResistencia,int pPosX,int pPosY);
    ~Torre();


};

Torre::Torre() {
    ataque=1000;
    resistencia=2500;
    posX=rand()%1271+15;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA2.png");
    id=typeid(Torre).name();
    velocidad=2;
}
Torre::Torre(int pResistencia, int pPosX, int pPosY) {
    ataque=1000;
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA2.png");
    velocidad=2;
    id=typeid(Torre).name();
}

Torre::~Torre() {

}




#endif //AIRWAR_TORRE_H

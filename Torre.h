//
// Created by alfredo on 22/03/17.
//

#ifndef AIRWAR_TORRE_H
#define AIRWAR_TORRE_H


#include "Elemento.h"

class Torre : public Elemento{
public:
    int pasos;
    Torre();
    Torre(int pResistencia,int pPosX,int pPosY);
    ~Torre();
};

Torre::Torre() {
    resistencia=200;
    posX=rand()%1160+15;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA2.png");
    id="TR";
    velocidad=2;
}
Torre::Torre(int pResistencia, int pPosX, int pPosY) {
    resistencia=pResistencia;
    posX=pPosX;
    posY=pPosY;
    imagen=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/torreA2.png");
    velocidad=2;
    id="TR";
}

Torre::~Torre() {

}


#endif //AIRWAR_TORRE_H
